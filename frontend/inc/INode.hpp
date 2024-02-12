#ifndef INODE_HPP_
#define INODE_HPP_

#include "types.hpp"

namespace paracl
{

class INode
{
    public:

        INode* parent_ = nullptr;

        Type_t type    = NoType;

        virtual ~INode () {}

        virtual void Dump () = 0;
};

} // end of paracl namespace

#endif