#include "driver.hpp"
#include "Node.hpp"
#include "AST.hpp"

#include <list>

int yyFlexLexer::yywrap() { return 1; }

int main() 
{
    std::ofstream file{};

    using namespace paracl;

    FlexLexer *lexer = new yyFlexLexer;

    yy::Driver driver(lexer);

    driver.Parse();

    delete lexer;

    AST tree;

    tree.root_ = new Digit();

    tree.Dump();

    delete tree.root_;
}