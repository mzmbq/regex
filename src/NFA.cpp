#include "NFA.h"
#include <cassert>

State ENFA::id = 0;

ENFA::ENFA()
{
    start = creteState();
    end = creteState();
    addEpsilonTransition(start, end);
}

ENFA::ENFA(char symbol)
{
    start = creteState();
    end = creteState();
    addTransition(start, end, symbol);
}

void ENFA::append(const ENFA& other)
{
    transitions.insert(other.transitions.begin(), other.transitions.end());
    epsilonTransitions.insert(other.epsilonTransitions.begin(), other.epsilonTransitions.end());
}

State ENFA::creteState()
{
    return id++;    
}

State ENFA::getStart() const
{
    return start;
}

State ENFA::getEnd() const
{
    return end;
}

void ENFA::addTransition(State from, State to, char symbol)
{
    Transition tmp{from, symbol};
    transitions[tmp] = to;
}

void ENFA::addEpsilonTransition(State from, State to)
{
    epsilonTransitions[from].push_back(to);
    // Thompson’s NFA allows max two epsilon transitions
    assert(epsilonTransitions[from].size() <= 2);
}

void ENFA::concat(const ENFA& other)
{
    addEpsilonTransition(this->end, other.start);
    this->end = other.end;
    append(other);
}

void ENFA::union_(const ENFA& other)
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

void ENFA::closure()
{
    State s = creteState();
    State e = creteState();

    addEpsilonTransition(s, e);
    addEpsilonTransition(s, this->start);
    addEpsilonTransition(this->end, e);
    addEpsilonTransition(this->end, this->start);
}


