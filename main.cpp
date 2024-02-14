#include "driver.hpp"
#include "Node.hpp"

#include <list>

int yyFlexLexer::yywrap() { return 1; }

int main() 
{
    using namespace paracl;

    FlexLexer *lexer = new yyFlexLexer;

    yy::Driver driver(lexer);

    driver.Parse();

    delete lexer;
}