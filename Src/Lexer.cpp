#include <iostream>

#include "../Include/Lexer.h"
#include "../Include/Token.h"

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


    return tokens;
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


bool Lexer::match(char excepted)
{
    if(IsAtEnd())
    {
        return false;
    }


    if(source[current]!=char excepted)
    {
        return false;
    }

    current++;
    return true;
}



void Lexer::AddToken(Token_type type)
{
    std::string text = source.substr(start, current - start);
    tokens.push_back
    (
      Token(
           type,
           text,
           "",
           line
           )
     );
}




void Lexer::AddToken(Token_type type, std::string literal)
{
    std::string text = source.substr(start, current- start);

    tokens.push_back
    (
       Token
       (
         type,
         text,
         literal,
         line
        )
     );
}

void Lexer::scanToken()
{
    char c = advance();



    if(IsDigit(c))
    {
        Number();
        return;
    }


    if(IsAlpha(c))
    {
        Identifier();
        return;
    }


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


        default:
            std::cerr << "Unexpected character '" << c
            <<"'at line"<<line<<std::endl;
            break;


    }

}



bool Lexer::IsAlpha(char c)
{
    return(c>='a' && c <='z') ||
          (c>= 'A' && c <= 'Z') ||
          c == '_';
}


bool Lexer::IsAlphaNumber(char c)
{
    return IsAlpha(c) || IsDigit(c);
}


bool Lexer::IsDigit(char c)
{
    return (c>='0' && c<='9');
}


void Lexer::Number()
{
    while(IsDigit(peek()))
    {
        advance();
    }

    if(peek() == '.' && IsDigit(peekNext()))
    {
        advance();



        while(IsDigit(peek()))
        {
             advance();
        }
    }

   AddToken(Token_type::NUMBER);


}





void Lexer::Identifier()
{
    while(IsAlphaNumber(peek()))
    {
        advance();
    }

    std::string text = source.substr(
                                     start,
                                     current - start
                                     );



    if(text == "let")
       {
           AddToken(Token_type::LET);
       }

    else if(text == "string")
    {
        AddToken(Token_type::STRING_TYPE);
    }

    else if(text == "bool")
    {
        AddToken(Token_type::BOOL);
    }

    else if(text == "function")
    {
        AddToken(Token_type::FUNCTION);
    }

    else if(text == "return")
    {
        AddToken(Token_type::RETURN);
    }
    else if(text == "print")
    {
        AddToken(Token_type::PRINT);
    }
    else if(text == "if")
    {
        AddToken(Token_type::IF);
    }
    else if(text == "else")
    {
        AddToken(Token_type::ELSE);
    }
    else if(text == "while")
    {
        AddToken(Token_type::WHILE);
    }

    else if(text == "true")
    {
        AddToken(Token_type::TRUE);
    }
    else if(text == "false")
    {
        AddToken(Token_type::FALSE);
    }

    else
    {
        AddToken(Lexer::Identifier);
    }

}








