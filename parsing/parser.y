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
%nterm <int> equals expr strongexpr var
%nterm print
%nterm printing

%start program

%%

program: eqlist
;

eqlist: equals SEMICOLON eqlist 
    | print SEMICOLON eqlist
    | %empty
;

equals: VAR ASG expr   { 
                            driver->vars_[$1] = $3;
                            /*std::cout << driver->vars_[$1] << std::endl;*/
                          }
;

expr: expr PLUS strongexpr { $$ = $1 + $3; }
    | expr MINUS strongexpr { $$ = $1 - $3; }
    | strongexpr { $$ = $1; }
;

strongexpr: strongexpr MULT var { $$ = $1 * $3; }
    | strongexpr DIVIDE var { $$ = $1 / $3; }
    | var
;

var: DIGIT       
    | VAR           { $$ = driver->vars_[$1]; }
;

print: PRINT LEFT_BRACKET printing RIGHT_BRACKET
;

printing: DIGIT { std::cout << $1 << std::endl; }
    | VAR { std::cout << driver->vars_[$1] << std::endl; }
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