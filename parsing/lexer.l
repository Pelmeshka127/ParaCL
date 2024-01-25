%option c++

%{

using std::cout;
using std::endl;

%}

WS      [ \t\n\v]+
DIGIT   [0-9]
DIGIT1  [1-9]
OP      [\+\-\=\/\%]
VAR     [a-zA-Z_][a-zA-Z_0-9_]*

%%

{WS}              /* skip blanks and tabs */
{OP}              { cout << "operator <" << yytext << ">" << endl; return 1; }
{DIGIT1}{DIGIT}*  { cout << "  number <" << yytext    << ">" << endl; return 1; }
"while"         { cout << " while <" << yytext << ">" << endl; return 1; }
{VAR}               { cout << "variable <" << yytext << ">" << endl; return 1; }
.                 { cout << " UNKNOWN <" << yytext << ">" << endl; return 1; }

%%