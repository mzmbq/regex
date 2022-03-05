#include <iostream>
#include "NFA.h"
#include "RegexParser.h"

int main(int, char**)
{
    // std::cout << insertExplicitConcatOperator("(aa)|(abc)*");

   NFA nfa = RegexParser{"a(a|b*)"}.compile();


    std::cout << std::endl;;
}