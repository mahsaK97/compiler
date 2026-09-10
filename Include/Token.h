#ifndef TOKEN_H
#define TOKEN_H

#include <string>


enum class Token_type
{

   LEFT_PAREN,
   RIGHT_PAREN,

   LEFT_BRACE,
   RIGHT_BRACE,

   LEFT_BRACKET,
   RIGHT_BRACKET,

   COMMA,
   SEMICOLON,

   PLUS,
   MINUS,
   STAR,
   SLASH,

   BANG,
   EQUAL,

   LESS,
   GREATER,

   BANG_EQUAL,
   EQUAL_EQUAL,

   LESS_EQUAL,
   GREATER_EQUAL,

   AND_AND,
   OR_OR,

   IDENTIFIER,
   STRING,
   NUMBER,

   LET,
   STRING_TYPE,
   BOOL,
   FUNCTION,
   RETURN,
   PRINT,
   IF,
   ELSE,
   WHILE,
   TRUE,
   FALSE,

   END_OF_FILE

};

class Token
{
public:
    Token_type type;
    std::string lexeme;
    std::string literal;
    int line;

    Token
    (
         Token_type type,
         std::string lexeme,
         std::string literal,
         int line
    );


};


#endif // TOKEN_H
