#ifndef INODE_HPP_
#define INODE_HPP_

#include <iostream>

#include "types.hpp"

namespace paracl
{

//======================================================================================//

class INode
{
    public:

        Type_t type_    = Type_t::NoType;

        INode(Type_t type = Type_t::NoType) : type_{type} {}

        virtual ~INode () 
        {
            std::cout << "Deleting Inode" << std::endl;
        }

        virtual void Dump () const = 0;
};

//======================================================================================//

} // end of paracl namespace

#endif