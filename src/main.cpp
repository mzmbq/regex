#include <iostream>
#include "NFA.h"

int main(int, char**)
{
    // std::cout << insertExplicitConcatOperator("(aa)|(abc)*");

   ENFA test('a');
   ENFA test2('b');
   test.union_(test2);



    std::cout << std::endl;;
}