#include "..../Include/Parser.h"


std::unique_ptr<Expr> Parser::primary()
{
    if(match ({Token_type::NUMBER, Token_type::STRING}))
        {
            auto expr = std::make_unique<LiteralExpr>();
            expr -> value = previous().lexeme();
            expr -> type = previous().type();
            return expr;
        }

    if match(({Token_type::TRUE, Token_type::FALSE}))
        {
            auto expr =std::make_unique<literalExpr>();
            expr ->value = previous().lexeme();
            expr ->type = previous().type();
            return expr;
        }

    if(match({Token_type::IDENTIFIER}))
        {
            auto expr= std::make_unique<variableExpr>();
            expr ->name= previous;
            return expr;
        }

    if(match({Token_type::LEFT_PAREN}))
        {
            auto expr = expression();
            consum(Token_type::RIGHT_PAREN,"EXCEPT ')' AFTER STATEMENT.");
            return expr;
        }

    if(match({Token_type::LEFT_BRACKET}))
        {
            auto arr = std::make_unique<ArrayExpr>();
            if(!check({Token_type::RIGHT_BRACKET}))
                {
                    do
                    {
                        arr->elements.push_back(expression());

                    }
                    while(match({Token_type::COMMA}));
                }
            consum(Token_type::RIGHT_BRACKET, "EXCEPT ']' AFTER STATEMENT.");
            return arr;
        }
        throw std::runtime_error("except a statement.");
}






std::unique_ptr<Expr> Parser::term()
{
    auto expr =factor();
    while(match({Token_type::PLUS, Token_type::MINUS}))
        {
            Token op = previous;
            auto right = factor();
            auto binary =  std::make_unique<binaryExpr>();
            binary->left= std::move(expr);
            binary->op = op;
            binary->right = std::move(right);
            expr = std::move(binary);
        }

        return expr;
}

std::unique_ptr<Stms>Parser::statement()
{
    if(match({Token_type::PRINT})) return printStatement;
    if(match({Token_type::IF})) return ifStatement;
    if(match({Token_type::WHILE})) return whileStatement;
    if(match({Token_type::FUNCTION})) return functionDeclStatement;
    if(match({Token_type::RETURN})) return returnStatement;


}
















