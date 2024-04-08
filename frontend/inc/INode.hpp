#ifndef INODE_HPP_
#define INODE_HPP_

#define DUMP

#include <iostream>

#include "types.hpp"

namespace paracl
{

//======================================================================================//

class INode
{
    public:

        INode(Type_t type = Type_t::NoType) : type_{type} {}

        virtual ~INode () 
        {
            std::cout << "Deleting Inode" << std::endl;
        }

        virtual void    Dump (std::ofstream& graph_file) const = 0;

        virtual int     Execute () const = 0;

        Type_t          GetNodeType() const { return type_; }

    private:

        Type_t type_ = Type_t::NoType;
};

//======================================================================================//

} // end of paracl namespace

#endif