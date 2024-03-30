#include "AST.hpp"

#ifdef DUMP

static int graph_num = 1;

static std::ofstream graph_file{};

#endif

namespace paracl
{

//======================================================================================//

Digit* AST::MakeDigit(int value)
{
    auto node = std::make_unique<Digit>(value);

    smart_nodes.push_back(std::move(node));

    return static_cast<Digit*>(smart_nodes.back().get());
}

//======================================================================================//

Variable* AST::MakeVar(std::string name)
{
    auto node = std::make_unique<Variable>(name);

    smart_nodes.push_back(std::move(node));

    return static_cast<Variable*>(smart_nodes.back().get());
}

//======================================================================================//

BinOp* AST::MakeBinOp(Operators op_type, INode* left, INode* right)
{
    auto node = std::make_unique<BinOp>(op_type, left, right);

    smart_nodes.push_back(std::move(node));

    return static_cast<BinOp*>(smart_nodes.back().get());
}

//======================================================================================//

LogOp* AST::MakeLogOp(LogicalOperator log_type, INode* left, INode* right)
{
    auto node = std::make_unique<LogOp>(log_type, left, right);

    smart_nodes.push_back(std::move(node));

    return static_cast<LogOp*>(smart_nodes.back().get());
}

//======================================================================================//

Print* AST::MakePrint(INode* expression)
{
    auto node = std::make_unique<Print>(expression);

    smart_nodes.push_back(std::move(node));

    return static_cast<Print*>(smart_nodes.back().get());
}

//======================================================================================//

Input* AST::MakeInput(INode* var)
{
    auto node = std::make_unique<Input>(var);

    smart_nodes.push_back(std::move(node));

    return static_cast<Input*>(smart_nodes.back().get());
}

//======================================================================================//

Scope* AST::MakeScope(INode* left, Scope* right)
{
    auto node = std::make_unique<Scope>(left, right);

    smart_nodes.push_back(std::move(node));

    return static_cast<Scope*>(smart_nodes.back().get());
}

//======================================================================================//

void AST::Dump() const
{
    #ifdef DUMP

    graph_file.open("../graphics/graph.dot");

    graph_file << "digraph Tree\n{\n";
    
    graph_file << "   rankdir = HR;\n";

    graph_file << "   tree[shape = Mrecord, style = filled, color = \"white\", style = filled, fontcolor = \"white\", fillcolor = \"blueviolet\", "
                        "label = \"AST Tree\"];\n";

    root_.get()->Dump(graph_file);
    
    graph_file << "   tree -> \"" << root_ << "\" [color = \"blueviolet\"];\n";
    
    graph_file << "}";

    graph_file.close();

    char call_graph[100] = " ";

    sprintf(call_graph, "dot ../graphics/graph.dot -Tpng -o ../graphics/graph%d.png", graph_num++);
    
    system(call_graph);

    #endif
}

//======================================================================================//

} // end of paracl namespace