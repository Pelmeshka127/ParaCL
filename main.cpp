#include "driver.hpp"

int yyFlexLexer::yywrap() { return 1; }

int main() 
{
    FlexLexer *lexer = new yyFlexLexer;

    yy::Driver driver(lexer);

    driver.Parse();

    delete lexer;
}