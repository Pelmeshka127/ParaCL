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
%nterm <int> equals
%nterm <int> expr
%nterm <int> arith

%start program

%%

program: eqlist
;

eqlist: equals SEMICOLON eqlist
      | %empty
;

equals: expr ASG expr   { 
                            $$ = ($1 == $3); 
                            std::cout << "Checking: " << $1 << " vs " << $3 
                                      << "; Result: " << $$
                                      << std::endl; 
                          }
;

expr: DIGIT arith        { $$ = $1 + $2; }
;

arith: PLUS DIGIT arith  { $$ = $2 + $3; }
     | MINUS DIGIT arith { $$ = -$2 + $3; }
     | %empty             { $$ = 0; }
;

%%

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         Driver* driver)
{
  return driver->yylex(yylval);
}

void parser::error(const std::string&){}
}
