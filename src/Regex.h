#ifndef __REGEX_H__
#define __REGEX_H__

#include "NFA.h"
#include <string>

class Regex
{
public:
    Regex(NFA& nfa);
    Regex(std::string string);

    bool test(std::string word);

private:
    NFA nfa;
};

#endif // __REGEX_H__