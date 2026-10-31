#include <iostream>

#include "../Include/Lexer.h"


int main()
{
    std::string source = "let x = 234";
    try
    {
        Lexer lexer(source);
        std::vector<Token> tokens = lexer.scanTokens();

        for(const auto &token :tokens)
            {
                 std::cout <<token.lexeme <<std::endl;
            }


    }

    catch(const std::runtime_error &error)
    {
        std::cerr << "Lexer Error: "
                  << error.what()<< std::endl;
        return 1;
    }

    return 0;
}
