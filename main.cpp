#include "driver.hpp"
#include "AST.hpp"
#include "executor.hpp"

int yyFlexLexer::yywrap() { return 1; }

int main() 
{
    using namespace paracl;

    FlexLexer *lexer = new yyFlexLexer;

    yy::Driver driver(lexer);

    driver.Parse();

    Executor executor;

    executor.Execute(driver.tree);

    // if (driver.tree.root_)
    //     driver.tree.Dump();

    return 0;
}