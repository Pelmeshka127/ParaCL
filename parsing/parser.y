%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::Driver* driver}

%code requires
{
#include <iostream>
#include <string>

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
%nterm <int> equals expression plusminus multdiv var logoperator
%nterm print
%nterm input
%nterm if
%nterm while

%start program

%%

program: eqlist
;

eqlist: equals SEMICOLON eqlist 
    | print SEMICOLON eqlist
    | input SEMICOLON eqlist
    | if SEMICOLON eqlist
    | %empty
;

equals: VAR ASG expression { 
                            driver->vars_[$1] = $3;
                            /*std::cout << driver->vars_[$1] << std::endl;*/
                            /*driver->tree.nodes.push_back(new paracl::BinOp(paracl::Operators::Plus));*/
                        }
;

expression: logoperator
;

logoperator: plusminus EQUAL plusminus { $$ = $1 == $3; }
    | plusminus NOT_EQUAL plusminus { $$ = $1 != $3; }
    | plusminus ABOVE plusminus { $$ = $1 > $3; }
    | plusminus EQ_ABOVE plusminus { $$ = $1 >= $3; }
    | plusminus BELOW plusminus { $$ = $1 < $3; }
    | plusminus EQ_BELOW plusminus { $$ = $1 <= $3; }
    | plusminus { $$ = $1; }
;

plusminus: plusminus PLUS multdiv { $$ = $1 + $3; }
    | plusminus MINUS multdiv { $$ = $1 - $3; }
    | multdiv { $$ = $1; }
;

multdiv: multdiv MULT var { $$ = $1 * $3; }
    | multdiv DIVIDE var { $$ = $1 / $3; }
    | var
;

var: DIGIT { $$ = $1; } 
    | VAR { $$ = driver->vars_[$1]; }
    | LEFT_BRACKET plusminus RIGHT_BRACKET { $$ = $2; }
;

print: PRINT LEFT_BRACKET logoperator RIGHT_BRACKET { std::cout << $3 << std::endl; }
;

input: VAR ASG INPUT
{
    int n{};

    std::cin >> n;

    std::cout << n << std::endl;

    driver->vars_[$1] = n;
}

if: IF LEFT_BRACKET logoperator RIGHT_BRACKET LEFT_BRACE eqlist RIGHT_BRACE
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