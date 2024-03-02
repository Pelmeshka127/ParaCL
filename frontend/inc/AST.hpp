#ifndef AST_HPP_
#define AST_HPP_

#include "INode.hpp"
#include "Node.hpp"

#include <vector>
#include <memory>

namespace paracl
{

//======================================================================================//

class AST final
{
    public:

        AST() = default;

        std::unique_ptr<paracl::INode> root_ = nullptr;

        std::vector<std::unique_ptr<paracl::INode>> smart_nodes{};

        void Dump() const;

        // void MakeBinOp(Operators op_type);

        ~AST() = default;
};

//======================================================================================//

// void AST::MakeBinOp(Operators op_type)
// {

// }

//======================================================================================//

} // end of paracl namespace

#endif