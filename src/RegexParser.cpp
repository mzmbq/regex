#include "RegexParser.h"
#include <string>
#include <sstream>
#include <cassert>
#include <iostream>

std::string insertExplicitConcatOperator(std::string str)
{
    std::stringstream output{};
    for (int i = 0; i < str.size(); i++)
    {
        char token = str[i];
        output << token;
        if (token == '(' || token == '|')
        {
            continue;
        }
        if (i < str.size() - 1)
        {
            char lookahead = str[i + 1];
            if (lookahead == '*' || lookahead == '?' || lookahead == '+' || lookahead == '|' || lookahead == ')') {
                continue;
            }
             output << '.';
        }
    }
    return output.str();
}

RegexParser::RegexParser(std::string input)
    : input{input},
    
     it{this->input.begin()}
{
}

std::string RegexParser::consumeToken()
{
    if (it == input.end())
    {
        return "";
    }
    return std::string{*it++};
}
    
std::string RegexParser::peekToken()
{
    if (it == input.end())
    {
        return "";
    }
    return std::string{*it};
}

NFA RegexParser::compile()
{
    NFA nfa = parseE();
    std::string tmp = peekToken();
    if (tmp != "")
    {
        std::cerr << "Syntax error" << std::endl;
    }
    return nfa;
}

NFA RegexParser::parseE()
{
    NFA tmp = parseT();
    while (peekToken() == "|")
    {
        consumeToken();
        NFA tmp2 = parseT();
        tmp.union_(tmp2);
    }
    return tmp;
}

NFA RegexParser::parseT()
{
    NFA tmp = parseF();
    while (peekToken() == ".")
    {
        consumeToken();
        NFA tmp2 = parseF();
        tmp.concat(tmp2);
    }
    return tmp;
}

NFA RegexParser::parseF()
{
    NFA tmp = parseP();
    if (peekToken() == "*")
    {
        consumeToken();
        tmp.closure();
    }
    return tmp;
}

NFA RegexParser::parseP()
{
    if (peekToken() == "(")
    {
        consumeToken();
        NFA tmp = parseE();
        if (peekToken() != ")")
        {
            std::cerr << "Syntax error: no parentheses" << std::endl;
        }
        consumeToken();
        return tmp;
    }
    else
    {
        NFA tmp = parseV();
        return tmp;
    }
}

NFA RegexParser::parseV()
{
    std::string symbol = consumeToken();
    NFA tmp{symbol[0]};
    return tmp;
}