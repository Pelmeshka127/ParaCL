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

        AST()
        {
            smart_nodes.reserve(20);
        }

        
        std::unique_ptr<paracl::INode> root_ = nullptr;

        std::vector<std::unique_ptr<paracl::INode>> smart_nodes{};

        
        void        Dump() const;

        Digit*      MakeDigit(int value);

        Variable*   MakeVar(std::string name);

        
        BinOp*      MakeBinOp(Operators op_type, INode* left = nullptr, INode* right = nullptr);

        ~AST() = default;
};

//======================================================================================//


//======================================================================================//

} // end of paracl namespace

#endif