%option c++

%{

#include <iostream>
#include "parser.hpp"

using std::cout;
using std::endl;

%}


WS      [ \t\n\v]+
DIGIT   -|[0-9]
DIGIT1  [1-9]
VAR     [a-zA-Z_][a-zA-Z_0-9_]*

%%

{WS}                /* skip blanks and tabs */

"+"                 { return yy::parser::token::PLUS; }
"-"                 { return yy::parser::token::MINUS; }
"*"                 { return yy::parser::token::MULT; }
"/"                 { return yy::parser::token::DIVIDE; }
"="                 { return yy::parser::token::ASG; }
">="                { return yy::parser::token::EQ_ABOVE; }
">"                 { return yy::parser::token::ABOVE; }
"<="                { return yy::parser::token::EQ_BELOW; }    
"<"                 { return yy::parser::token::BELOW; }
"=="                { return yy::parser::token::EQUAL; }
"!="                { return yy::parser::token::NOT_EQUAL; }

"?"                 { return yy::parser::token::INPUT; }
","                 { return yy::parser::token::COMMA; }
";"                 { return yy::parser::token::SEMICOLON; }
"("                 { return yy::parser::token::LEFT_BRACKET; }
")"                 { return yy::parser::token::RIGHT_BRACKET; }
"{"                 { return yy::parser::token::LEFT_BRACE; }
"}"                 { return yy::parser::token::RIGHT_BRACE; }

"while"             { return yy::parser::token::WHILE; }
"if"                { return yy::parser::token::IF; }
"else"              { return yy::parser::token::ELSE; }
"print"             { return yy::parser::token::PRINT; }

{DIGIT1}?{DIGIT}*   { return yy::parser::token::DIGIT; }
{VAR}               { return yy::parser::token::VAR; }

.                   { cout << " UNKNOWN <" << yytext << ">" << endl; return yy::parser::token::ERR; }

%%