#include <string>
#include "lex.cpp"
#include <iostream>

void inspectTokens(std::string source)
{
    Lexer lexer = Lexer(source);
    Token token = lexer.nextToken();

    while (token.type != EOf)
    {
        std::cout << token.text << " - " << token.type << std::endl;
        token = lexer.nextToken();
    }
}