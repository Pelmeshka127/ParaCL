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

%code
{
#include "driver.hpp"

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         Driver* driver);
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
%nterm print
%nterm input
%nterm if
%nterm while
%nterm <paracl::INode*> equal logoperator plusminus multdiv lval var

%start program

%%

program: eqlist
;

eqlist: equal SEMICOLON eqlist
    | %empty
;

equal: var ASG logoperator
{
    $$ = driver->tree.MakeBinOp(paracl::Operators::Asg, $1, $3);
}
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

var: VAR
{
    $$ = driver->tree.MakeVar($1);
}
;

%%

namespace yy 
{

parser::token_type yylex(parser::semantic_type* yylval, Driver* driver)
{
    return driver->yylex(yylval);
}

void parser::error(const std::string&){}

}