#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <fstream>

#include "INode.hpp"

namespace paracl
{

//======================================================================================//

class Variable final : public INode
{
    public:

        int x = 0;

        Variable(std::string name = "", int value = 0) 
            : INode(Type_t::Variable), name_{name}, value_{value} {}

        void Dump(std::ofstream& graph_file) const override;

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

        void Dump(std::ofstream& graph_file) const override;

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

        void Dump(std::ofstream& graph_file) const override;

        ~BinOp()
        {
            if (left_)
                delete left_;

            if (right_)
                delete right_;
                
            std::cout << "Deleting operator" << std::endl;
        }

    private:

        INode* left_  = nullptr;

        INode* right_ = nullptr;

        Operators operator_type_ = Operators::NoType;
};

//======================================================================================//

} // end of paracl namespace

#endif