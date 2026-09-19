#include <string>


#include "Token.h"
#include "Lexer.h"


class Expr
{
public:
    virtual ~Expr() = default;


};

class BinaryExpr: public Expr
{
public:
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

};



class UnaryExpr : public Expr
{
public:
    Token op;
    std::unique_ptr<Expr> right;
};

class LiteralExpr : public Expr
{
public:
    std::string value;
    Token_type type;
};


class VariableExpr : public Expr
{
public:
    Token name;
};


class AssignExpr : public Expr
{
public:
    Token name;
    std::unique_ptr<Expr>value;
};



class CallExpr : public Expr
{
public:
    std::unique_ptr<Expr> callee;
    std::vector<std::unique_ptr<Expr>>arguments;
};


class ArrayExpr :public Expr
{
public:
    std::vector<std::unique_ptr<Expr>> elements;

};

class IndexExpr: public Expr
{
public:
    std::unique_ptr<Expr> array;
    std::unique_ptr<Expr> index;
};





class Stms
{
public:
    virtual ~Stms() = default;

};


class ExprStms : public Stms
{
public:
    std::unique_ptr<Expr> expreesion;
};

class Printstms :public Stms
{
public:
    std::unique_ptr<Expr> expression;

};

class TypeDeclStms: public Stms
{
public:
    Token typeKeyword;
    Token name;
    std::unique_ptr<Expr> initializer;
};


class BlockStms :public Stms
{
public:
    std::vector<std::unique_ptr<Stms>> statement;
};


class IfStms : public Stms
{
public:
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stms> thenBranch;
    std::unique_ptr<Stms> elseBranch;

};

class WhileStms :public Stms
{
public:
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stms> body;
};

class FunctionStms:public Stms
{
public:
    Token name;
    std::vector<Token> parameters;
    std::vector<std::unique_ptr<Stms>> body;
};


class ReturnStms:public Stms
{
public:
    std::unique_ptr<Expr> value;
};




class Parser
{
public:
    Parser(::std::vector<Token> tokens);
    std::vector<std::unique_ptr<Stms>>Parser;
};
