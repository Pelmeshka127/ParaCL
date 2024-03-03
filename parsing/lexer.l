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

"+"                 { /*cout << "operator <" << yytext << ">" << endl;*/ return yy::parser::token::PLUS; }
"-"                 { /*cout << "operator <" << yytext << ">" << endl;*/; return yy::parser::token::MINUS; }
"*"                 { /*cout << "operator <" << yytext << ">" << endl;*/; return yy::parser::token::MULT; }
"/"                 { /*cout << "operator <" << yytext << ">" << endl;*/; return yy::parser::token::DIVIDE; }
"="                 { /*cout << "operator <" << yytext << ">" << endl;*/; return yy::parser::token::ASG; }
">="                { /*cout << "operator <" << yytext << ">" << endl;*/; return yy::parser::token::EQ_ABOVE; }
">"                 { /*cout << "operator <" << yytext << ">" << endl;*/; return yy::parser::token::ABOVE; }
"<="                { /*cout << "operator <" << yytext << ">" << endl;*/; return yy::parser::token::EQ_BELOW; }    
"<"                 { /*cout << "operator <" << yytext << ">" << endl;*/; return yy::parser::token::BELOW; }
"=="                { /*cout << "operator <" << yytext << ">" << endl;*/; return yy::parser::token::EQUAL; }
"!="                { /*cout << "operator <" << yytext << ">" << endl;*/; return yy::parser::token::NOT_EQUAL; }

"?"                 { /*cout << "special operator <" << yytext << ">" << endl*/; return yy::parser::token::INPUT; }
","                 { /*cout << "special operator <" << yytext << ">" << endl*/; return yy::parser::token::COMMA; }
";"                 { /*cout << "special operator <" << yytext << ">" << endl*/; return yy::parser::token::SEMICOLON; }
"("                 { /*cout << "special operator <" << yytext << ">" << endl*/; return yy::parser::token::LEFT_BRACKET; }
")"                 { /*cout << "special operator <" << yytext << ">" << endl*/; return yy::parser::token::RIGHT_BRACKET; }
"{"                 { /*cout << "special operator <" << yytext << ">" << endl*/; return yy::parser::token::LEFT_BRACE; }
"}"                 { /*cout << "special operator <" << yytext << ">" << endl*/; return yy::parser::token::RIGHT_BRACE; }

"while"             { /*cout << "key word <" << yytext << ">" << endl*/; return yy::parser::token::WHILE; }
"if"                { /*cout << "key word <" << yytext << ">" << endl*/; return yy::parser::token::IF; }
"print"             { /*cout << "key word <" << yytext << ">" << endl*/; return yy::parser::token::PRINT; }

{DIGIT1}?{DIGIT}*   { /*cout << "number <" << yytext << ">" << endl*/; return yy::parser::token::DIGIT; }
{VAR}               { /*cout << "variable <" << yytext << ">" << endl*/; yy::parser::make_VAR(yytext); return yy::parser::token::VAR; }

.                   { cout << " UNKNOWN <" << yytext << ">" << endl; return yy::parser::token::ERR; }

%%