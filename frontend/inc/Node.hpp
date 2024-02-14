#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>

#include "Inode.hpp"

namespace paracl
{

//======================================================================================//

class Variable final : public INode
{
    public:

        int x = 0;

        Variable(std::string name = "", int value = 0) 
            : INode(Type_t::Variable), name_{name}, value_{value} {}

        void Dump() const override
        {
            std::cout << "The variable " << name_ << "; The value " << value_ << std::endl;
        }

        ~Variable()
        {
            std::cout << "Deleting Variable" << std::endl;
        }

    private:

        std::string name_ = "";

        int value_ = 0;
};

//======================================================================================//

class Digit final : public INode
{
    public:

        Digit(int value = 0) 
            : INode(Type_t::Digit), value_{value} {}

        void Dump() const override
        {
            std::cout << "The value is " << value_ << std::endl;
        }

        ~Digit()
        {
            std::cout << "Deleting digit" << std::endl;
        }

    private:

        int value_ = 0;
};

//======================================================================================//

class BinOp final : public INode
{
    public:

        BinOp(Operators type, INode* left = nullptr, INode* right = nullptr) 
            : INode(Type_t::Operation), operator_type_{type}, left_{left}, right_{right} {}

        void Dump() const override
        {
            std::cout << "Operation " << static_cast<int>(operator_type_) << "; Left is " << left_ << "; right is " << right_ << std::endl;
        }

        ~BinOp()
        {
            std::cout << "Deleting operator" << std::endl;
        }

        void SetLeft(INode* left)
        {
            left_ = left;
        }

        void SetRight(INode* right)
        {
            right_ = right;
        }

    private:

        INode* left_  = nullptr;

        INode* right_ = nullptr;

        Operators operator_type_ = Operators::NoType;
};

//======================================================================================//

} // end of paracl namespace

#endif