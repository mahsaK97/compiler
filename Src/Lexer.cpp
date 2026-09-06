#include "Lexer.h"


Lexer::Lexer(std::string source)
{
    this->source= source;

}


std::vector<Token> Lexer::scanTokens()
{
    while(!IsAtEnd())
    {
        start = current;
        scanToken();

    }

    tokens.push_back(

                     Token(
                           Token_type::END_OF_FILE,
                           "",
                           "",
                           line
                           )
                     );


    return Tokens;
}





bool Lexer::IsAtEnd()
{
    return current >= source.length();
}






char Lexer::advance()
{
    return source[current++];
}



char Lexer::peek()
{
    if(IsAtEnd())
    {
        return '\0';
    }

    return source[current];
}



char Lexer::peekNext()
{
    if(current +1 >= source.length())
    {
        return '\0';
    }

    return source[current+1];
}





void Lexer::scanToken()
{
    char c = advance();


    switch (c)
    {
         case '(':
                AddToken(Token_type::LEFT_PAREN);
                break;

         case ')':
                AddToken(Token_type::RIGHT_PAREN);
                break;

         case '{':
            AddToken(Token_type::LEFT_BRACE);
            break;

         case '}':
            AddToken(Token_type::RIGHT_BRACE);
            break;

         case '[':
            AddToken(Token_type::LEFT_BRACKET);
            break;

         case ']':
            AddToken(Token_type::RIGHT_BRACKET);
            break;

         case ';':
            AddToken(Token_type::SEMICOLON);
            break;

         case ',':
            AddToken(Token_type::COMMA);
            break;

         case '+':
            AddToken(Token_type::PLUS);
            break;

         case '-':
            AddToken(Token_type::MINUS);
            break;

        case '*':
            AddToken(Token_type::STAR);
            break;

        case '/':
            if(match('/'))
            {
                while(peek() !='\n' && !IsAtEnd())
                {
                    advance();
                }
            }

            else
            {
                   AddToken(Token_type::SLASH);
            }

            break;

        case ' ':
        case '\t':
        case '\r':
            break;

        case '\n':
            line++;
            break;


        case '!':
            AddToken(match('=') ?Token_type::BANG_EQUAL
                     :Token_type::BANG);
            break;

        case '=':
            AddToken(match('=') ?Token_type::EQUAL_EQUAL
                     :Token_type::EQUAL);
            break;

        case '>':
            AddToken(match('=') ?Token_type::GREATER_EQUAL
                     :Token_type::GREATER);
            break;

        case '<':
            AddToken(match('=') ?Token_type::LESS_EQUAL
                     :Token_type::LESS);
            break;

        case '&':
            if(match('&'))
                AddToken(Token_type::AND_AND);
            break;

        case '|':
           if(match('|'))
             AddToken(Token_type::OR_OR);
             break;


    }
}










