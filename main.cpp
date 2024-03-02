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

    // driver.tree.nodes.push_back(new BinOp(Operators::Plus, new Variable("x"), new BinOp(Operators::Mult, new Digit(5), new Digit(6))));

    // driver.tree.root_ = *driver.tree.nodes.begin();

    if (driver.tree.root_)
        driver.tree.Dump();

    AST tree;

    // auto var = std::make_unique<Variable>("x");

    // auto num = std::make_unique<Digit>(17);

    // auto bin = std::make_unique<BinOp>(Operators::Asg, var.get(), num.get());

    // tree.smart_nodes.push_back(std::move(bin));

    // tree.smart_nodes.push_back(std::move(num));

    // tree.smart_nodes.push_back(std::move(var));

    // *(tree.smart_nodes.cend())->get();

    // tree.root_ = std::move(*tree.smart_nodes.begin());

    // tree.Dump();

    // auto node = std::make_unique<paracl::Digit>(13); 
    // tree.smart_nodes.push_back(std::move(node));
    // INode* g = node.get();

    return 0;
}