#include "NFA.h"
#include <cassert>

State NFA::id = 0;

NFA::NFA()
{
    start = creteState();
    end = creteState();
    addEpsilonTransition(start, end);
}

NFA::NFA(char symbol)
{
    start = creteState();
    end = creteState();
    addTransition(start, end, symbol);
}

void NFA::append(const NFA& other)
{
    transitions.insert(other.transitions.begin(), other.transitions.end());
    epsilonTransitions.insert(other.epsilonTransitions.begin(), other.epsilonTransitions.end());
}

State NFA::creteState()
{
    return id++;    
}

State NFA::getStart() const
{
    return start;
}

State NFA::getEnd() const
{
    return end;
}

void NFA::addTransition(State from, State to, char symbol)
{
    Transition tmp{from, symbol};
    transitions[tmp] = to;
}

void NFA::addEpsilonTransition(State from, State to)
{
    epsilonTransitions[from].push_back(to);
    // Thompson’s NFA allows max two epsilon transitions
    assert(epsilonTransitions[from].size() <= 2);
}

void NFA::concat(const NFA& other)
{
    addEpsilonTransition(this->end, other.start);
    this->end = other.end;
    append(other);
}

void NFA::union_(const NFA& other)
{
    State s = creteState();
    addEpsilonTransition(s, this->start);
    addEpsilonTransition(s, other.start);

    State e = creteState();
    addEpsilonTransition(this->end, e);
    addEpsilonTransition(other.end, e);

    this->start = s;
    this->end = e;
    append(other);
}

void NFA::closure()
{
    State s = creteState();
    State e = creteState();

    addEpsilonTransition(s, e);
    addEpsilonTransition(s, this->start);
    addEpsilonTransition(this->end, e);
    addEpsilonTransition(this->end, this->start);

    this->start = s;
    this->end = e;
}


