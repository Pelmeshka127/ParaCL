%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::Driver* driver}

%code requires
{
#include <iostream>
#include <string>
#include "AST.hpp"

// forward decl of argument to parser
namespace yy { class Driver; }
}

%locations

%code
{
#include "driver.hpp"

namespace yy 
{
    parser::token_type yylex(parser::semantic_type* yylval, yy::parser::location_type* loc, Driver* driver);
}

}

%token
    ASG           "="
    MINUS         "-"
    PLUS          "+"
    MULT          "*"
    DIVIDE        "/"
    EQUAL         "=="
    EQ_ABOVE      ">="
    ABOVE         ">"
    EQ_BELOW      "<="
    BELOW         "<"
    NOT_EQUAL     "!="
    INPUT         "?"
    COMMA         ","
    SEMICOLON     ";"
    LEFT_BRACKET  "("
    RIGHT_BRACKET ")"
    LEFT_BRACE    "{"
    RIGHT_BRACE   "}"
    WHILE         "while"
    IF            "if"
    PRINT         "print"
    ERR
;

%token <int>          DIGIT
%token <std::string>  VAR
%nterm <paracl::INode*> logoperator plusminus multdiv lval var 
%nterm <paracl::INode*> input print
%nterm <paracl::INode*> if else while
%nterm <paracl::INode*> stmt
%nterm <paracl::Scope*> stmts

%start program

%%

program: stmts
;

stmts: stmt SEMICOLON stmts { $$ = driver->tree.MakeScope($1, $3); }
    | %empty {}
;

stmt: var ASG logoperator { $$ = driver->tree.MakeBinOp(paracl::Operators::Asg, $1, $3); }
    | print { $$ = $1; }
    | input { $$ = $1; }
;

logoperator: logoperator EQUAL plusminus { $$ = driver->tree.MakeLogOp(paracl::LogicalOperator::Eq, $1, $3); }
    | logoperator NOT_EQUAL plusminus { $$ = driver->tree.MakeLogOp(paracl::LogicalOperator::NotEq, $1, $3); }
    | logoperator EQ_ABOVE plusminus { $$ = driver->tree.MakeLogOp(paracl::LogicalOperator::EqAbove, $1, $3); }
    | logoperator EQ_BELOW plusminus { $$ = driver->tree.MakeLogOp(paracl::LogicalOperator::EqBelow, $1, $3); }
    | logoperator ABOVE plusminus { $$ = driver->tree.MakeLogOp(paracl::LogicalOperator::Above, $1, $3); }
    | logoperator BELOW plusminus { $$ = driver->tree.MakeLogOp(paracl::LogicalOperator::Below, $1, $3); }
    | plusminus

plusminus: plusminus PLUS multdiv { $$ = driver->tree.MakeBinOp(paracl::Operators::Plus, $1, $3); }
    | plusminus MINUS multdiv { $$ = driver->tree.MakeBinOp(paracl::Operators::Minus, $1, $3); }
    | multdiv
;

multdiv: multdiv MULT lval { $$ = driver->tree.MakeBinOp(paracl::Operators::Mult, $1, $3); }
    | plusminus DIVIDE lval { $$ = driver->tree.MakeBinOp(paracl::Operators::Divide, $1, $3); }
    | lval
;

lval: DIGIT { $$ = driver->tree.MakeDigit($1); }
    | VAR { $$ = driver->tree.MakeVar($1);}
    | LEFT_BRACKET logoperator RIGHT_BRACKET { $$ = $2; }
;

var: VAR { $$ = driver->tree.MakeVar($1); std::cout << "Var name is: " << $1 << std::endl; }
;

print: PRINT LEFT_BRACKET logoperator RIGHT_BRACKET { $$ = driver->tree.MakePrint($3); }
;

input: var ASG INPUT { $$ = driver->tree.MakeInput($1); }
;

if: LEFT_BRACKET logoperator RIGHT_BRACKET LEFT_BRACE stmts RIGHT_BRACE
;

else: LEFT_BRACE stmts RIGHT_BRACE
;

while: LEFT_BRACKET logoperator RIGHT_BRACKET LEFT_BRACE stmts RIGHT_BRACE
;

%%

namespace yy 
{

parser::token_type yylex(parser::semantic_type* yylval, yy::parser::location_type* loc, Driver* driver)
{
    return driver->yylex(yylval, loc);
}

void parser::error(const location_type& l, const std::string& m){}

}