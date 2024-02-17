#include "AST.hpp"

namespace paracl
{

//======================================================================================//

void AST::Dump() const
{
    #ifdef DUMP

    graph_file.open("../graphics/graph.dot");

    graph_file << "digraph Tree\n{\n";
    
    graph_file << "   rankdir = HR;\n";

    graph_file << "   tree[shape = Mrecord, style = filled, color = \"white\", style = filled, fontcolor = \"white\", fillcolor = \"blueviolet\", "
                        "label = \"AST Tree\"];\n";

    root_->Dump(graph_file);
    
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