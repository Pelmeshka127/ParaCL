#ifndef AST_HPP_
#define AST_HPP_

#include "INode.hpp"
#include "Node.hpp"

#include <vector>

namespace paracl
{

//======================================================================================//    

class AST final
{
    public:

        AST() = default;

        INode* root_ = nullptr;

        void Dump() const;

        std::vector<paracl::INode*> nodes{};

        ~AST() 
        {
            auto begin = nodes.begin(), end = nodes.end();

            for (auto it = begin; it != end; ++it)
                delete *it;
        }
};

//======================================================================================//

//======================================================================================//

} // end of paracl namespace

#endif