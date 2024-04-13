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

        // Assignment* MakeAsg(Variable* left = nullptr, INode* right = nullptr);

        BinOp*      MakeBinOp(Operators op_type, INode* left = nullptr, INode* right = nullptr);

        LogOp*      MakeLogOp(LogicalOperator log_type, INode* left = nullptr, INode* right = nullptr);

        Scope*      MakeScope(INode* left = nullptr, Scope* right = nullptr);

        Statement*  MakeStatement(KeyWords type, INode* left = nullptr, INode* right = nullptr);


        ~AST() = default;
};

//======================================================================================//


//======================================================================================//

} // end of paracl namespace

#endif