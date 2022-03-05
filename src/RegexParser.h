#ifndef __REGEXPARSER_H__
#define __REGEXPARSER_H__

#include <string>
#include "NFA.h"



/*
Grammar:
E -> T {"|" T}
T -> F {"." F}
F -> P ["*"]
P -> V | "(" E ")"
*/

class RegexParser
{
public:
    RegexParser(std::string input);
    std::string insertExplicitConcatOperator(std::string);

    std::string consumeToken();
    std::string peekToken();

    // generate NFA from regex string
    NFA compile();

    NFA parseE();
    NFA parseT();    
    NFA parseF();    
    NFA parseP();    
    NFA parseV();    

private:
    std::string input;
    std::string::iterator it;
};

#endif // __REGEXPARSER_H__