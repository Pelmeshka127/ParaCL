#ifndef INODE_HPP_
#define INODE_HPP_

namespace paracl
{

class INode
{
    public:

        INode* parent_ = nullptr;

        virtual ~INode () {}
};

} // end of paracl namespace

#endif