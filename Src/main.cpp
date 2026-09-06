#include <iostream>

#include "lexer.h"


int main()
{
    std::string source = "let x = 234";
    Lexer lexer(source);
    std::vetor<Token> tokens = lexer.scanTokens();

    for(const auto &token :tokens)
    {
        std::cout <<token.lexeme <<std::endl;
    }

    return 0;
}
