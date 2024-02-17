#ifndef AST_HPP_
#define AST_HPP_

#ifdef DUMP

static int graph_num = 1;

static std::ofstream graph_file{};

#endif

#include "Inode.hpp"
#include "Node.hpp"

namespace paracl
{

class AST final
{
    public:

        AST() = default;

        INode* root_ = nullptr;

        void Dump() const
        {
            #ifdef DUMP

            graph_file.open("graph.dot");

            graph_file << "digraph Tree\n{\n";
            
            graph_file << "   rankdir = HR;\n";
            
            graph_file << "   node[fontsize=14];\n   edge[color=\"black\",fontcolor=\"blue\",fontsize=12];\n";
            
            // graph_file << "   tree[shape = Mrecord, style = filled, fillcolor = \"chartreuse1\", "
            //                     "label = \"My Tree | size = " << tree->Size() << "\"];\n";

            root_->Dump(graph_file);
            
            // graph_file << "   tree -> \"" << tree->Root() << "\" [color = \"gray0\"];\n";
            
            graph_file << "}";

            graph_file.close();

            char call_graph[100] = " ";

            sprintf(call_graph, "dot graph.dot -Tpng -o graph%d.png", graph_num++);
            
            system(call_graph);

        #endif

        }

        ~AST()
        {
            // delete root_;
        }
};

} // end of paracl namespace

#endif