#ifndef LEXER_H
#define LEXER_H


#include <string>
#include <vector>
#include "Token.h"


class Lexer
{
private:

    std::string source;
    std::vector<Token>tokens;

    int start =0;
    int current = 0;
    int line =1;


public:

    Lexer(std::string source);
    std::vector <Token> scanTokens();



private:
    void scanToken();

    char advance();
    char peek();
    char peekNext();


    bool IsAtEnd();


    void AddToken(Token_type type, std::string literal = "");
    void Identifier();
    void Number();
    void String();


    bool match(char expected);
    bool IsDigit(char c);
    bool IsAlpha(char c);
    bool IsAlphaNumber(char c);

};




#endif
