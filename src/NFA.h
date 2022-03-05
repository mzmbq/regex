#ifndef __STATE_H__
#define __STATE_H__

#include <vector>
#include <unordered_map>
#include <utility>
#include <vector>

using State = unsigned int;
struct Transition
{
    State state;
    char symbol;

    bool operator==(const Transition& other) const
    {
        return state == other.state && symbol == other.symbol;
    }
};

struct hash_fn
{
    std::size_t operator() (const Transition& t) const
    {
        std::size_t h1 = std::hash<State>()(t.state);
        std::size_t h2 = std::hash<char>()(t.symbol);
        return h1 ^ h2;
    }
};

class NFA
{
    static State id;
public:
    NFA();
    NFA(char symbol);

    // copy transitions from another ENFA
    void append(const NFA& other);

    State creteState();

    State getStart() const;
    State getEnd() const;

    void addTransition(State from, State to, char symbol);
    void addEpsilonTransition(State from, State to);

    void concat(const NFA& other);
    void union_(const NFA& other);
    void closure();

private:
    State start;
    State end;
    std::unordered_map<Transition, State, hash_fn> transitions;
    std::unordered_map<State, std::vector<State>> epsilonTransitions;
};


#endif // __STATE_H__