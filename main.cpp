#include "driver.hpp"
#include "Node.hpp"
#include "AST.hpp"

#include <list>

int yyFlexLexer::yywrap() { return 1; }

int main() 
{
    // std::ofstream file{};

    using namespace paracl;

    // FlexLexer *lexer = new yyFlexLexer;

    // yy::Driver driver(lexer);

    // driver.Parse();

    // delete lexer;

    INode* num = new Digit(4);

    INode* var = new Variable("x", 3);

    AST tree;

    tree.root_ = new BinOp(Operators::Plus, var, num);

    tree.Dump();

    delete num;

    delete var;

    delete tree.root_;
}