#include "../Include/Parser.h"
#include <stdexcept>


bool Parser::isAtEnd()
{
    return peek().type ==Token_type::END_OF_FILE;
}

Token Parser::peek()
{
    return tokens[current];
}
Token Parser::previous()
{
    return tokens[current-1];
}
Token Parser::advance()
{
    if(!isAtEnd())
    {
        current++;
    }
    return previous();
}

bool Parser::check(Token_type type)
{
    if(isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::match(const std::vector<Token_type> &types)
{
    for(Token_type type: types)
    {
        if(check(type))
        {
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::consume(Token_type type , std::string messages)
{
    if(check(type)) return advance();
    throw std::runtime_error(
            "syntax error in line " + std::to_string(peek().line) + ": " +messages);
}


Parser::Parser(std::vector<Token> tokens): tokens(tokens){}

std::unique_ptr<Expr> Parser::primary()
{
    if(match ({Token_type::NUMBER, Token_type::STRING}))
        {
            auto expr = std::make_unique<LiteralExpr>();
            expr -> value = previous().lexeme;
            expr -> type = previous().type;
            return expr;
        }

    if (match({Token_type::TRUE, Token_type::FALSE}))
        {
            auto expr =std::make_unique<LiteralExpr>();
            expr ->value = previous().lexeme;
            expr ->type = previous().type;
            return expr;
        }

    if(match({Token_type::IDENTIFIER}))
        {
            auto expr= std::make_unique<VariableExpr>();
            expr ->name= previous();
            return expr;
        }

    if(match({Token_type::LEFT_PAREN}))
        {
            auto expr = expression();
            consume(Token_type::RIGHT_PAREN,"EXCEPT ')' AFTER STATEMENT.");
            return expr;
        }

    if(match({Token_type::LEFT_BRACKET}))
        {
            auto arr = std::make_unique<ArrayExpr>();
            if(!check(Token_type::RIGHT_BRACKET))
                {
                    do
                    {
                        arr->elements.push_back(expression());

                    }
                    while(match({Token_type::COMMA}));
                }
            consume(Token_type::RIGHT_BRACKET, "EXCEPT ']' AFTER STATEMENT.");
            return arr;
        }
        throw std::runtime_error("except a statement.");
}






std::unique_ptr<Expr> Parser::term()
{
    auto expr =factor();
    while(match({Token_type::PLUS, Token_type::MINUS}))
        {
            Token op = previous();
            auto right = factor();
            auto binary =  std::make_unique<BinaryExpr>();
            binary->left= std::move(expr);
            binary->op = op;
            binary->right = std::move(right);
            expr = std::move(binary);
        }

        return expr;
}

std::unique_ptr<Expr> Parser::factor()
{
    auto expr= unary();
    while(match({Token_type::STAR, Token_type::SLASH}))
        {
            Token op = previous();
            auto right = unary();

            auto binary = std::make_unique<BinaryExpr>();
            binary->left =std::move(expr);
            binary->op = op;
            binary-> right=std::move(right);
            expr=std::move(binary);
        }

    return expr;
}

std::unique_ptr<Expr> Parser::comparsion()
{
    auto expr = term();
    while(match({Token_type::GREATER , Token_type::LESS,
                Token_type::GREATER_EQUAL, Token_type::LESS_EQUAL}))
                    {
                        Token op =previous();
                        auto right = term();


                        auto binary = std::make_unique<BinaryExpr>();
                        binary->left = std::move(expr);
                        binary->op = op;
                        binary-> right = std::move(right);
                        expr= move(binary);

                    }
    return expr;

}




std::unique_ptr<Expr> Parser::equality()
{
    auto expr = comparsion();
    while(match({Token_type::BANG_EQUAL, Token_type::EQUAL_EQUAL}))
        {
            Token op = previous();
             auto right = comparsion();

             auto binary= std::make_unique<BinaryExpr>();

             binary->left =std::move(expr);
             binary->op = op;
             binary-> right = move(right);
             expr = move(binary);
        }

        return expr;
}


std::unique_ptr<Stms>Parser::Statement()
{
    if(match({Token_type::PRINT})) return PrintStatement();
    if(match({Token_type::IF})) return IfStatement();
    if(match({Token_type::WHILE})) return WhileStatement();
    if(match({Token_type::FUNCTION})) return FunctionDeclStatement();
    if(match({Token_type::RETURN})) return ReturnStatement();

    throw std::runtime_error("unexpected token in statement");


}
















