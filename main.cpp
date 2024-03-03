#include "driver.hpp"
#include "Node.hpp"
#include "AST.hpp"

int yyFlexLexer::yywrap() { return 1; }

int main() 
{
    using namespace paracl;

    FlexLexer *lexer = new yyFlexLexer;

    yy::Driver driver(lexer);

    driver.Parse();

    if (driver.tree.root_)
        driver.tree.Dump();

    return 0;
}