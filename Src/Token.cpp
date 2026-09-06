#include "Token.h"


Token::Token(


             Token_type type,
             std::string lexeme,
             std::string literal,
             int line

)

   :type(type),
   lexeme(lexeme),
   literal(literal),
   line(line)


   {

   }


