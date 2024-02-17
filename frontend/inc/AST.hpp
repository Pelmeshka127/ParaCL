#ifndef AST_HPP_
#define AST_HPP_

#include "Inode.hpp"
#include "Node.hpp"

#ifdef DUMP

static int graph_num = 1;

static std::ofstream graph_file{};

#endif

namespace paracl
{

class AST final
{
    public:

        AST() = default;

        INode* root_ = nullptr;

        void Dump() const;

        ~AST()
        {
            // delete root_;
        }
};

} // end of paracl namespace

#endif