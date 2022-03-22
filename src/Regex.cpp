#include "Regex.h"
#include "RegexParser.h"

Regex::Regex(NFA& nfa)
    : nfa(nfa)
{
    
}

Regex::Regex(std::string string)
{
    RegexParser parser{string};
    nfa = parser.compile();
}

bool Regex::test(std::string word)
{
    return nfa.testWord(word);
}

