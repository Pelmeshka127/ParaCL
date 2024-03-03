#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <fstream>

#include "INode.hpp"

namespace paracl
{

template <typename T> std::string GetSign(const T type);

//======================================================================================//

class Variable final : public INode
{
    public:

        Variable(std::string name = "") 
            : INode(Type_t::Variable), name_{name} {}

        void Dump(std::ofstream& graph_file) const override;

        ~Variable()
        {
            std::cout << "Deleting Variable" << std::endl;
        }

    private:

        std::string name_ = "";
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
            std::cout << "Deleting operator" << std::endl;
        }

        void SetLeft(INode* node)
        {
            left_ = node;
        }

        void SetRight(INode* node)
        {
            right_ = node;
        }

    private:

        INode* left_  = nullptr;

        INode* right_ = nullptr;

        Operators operator_type_ = Operators::NoType;
};

//======================================================================================//

class LogOp : public INode
{   
    public:

        LogOp(LogicalOperator type, INode* left = nullptr, INode* right = nullptr) 
            : INode(Type_t::LogOperation), operator_type_{type}, left_{left}, right_{right} {}

        void Dump(std::ofstream& graph_file) const override;

        ~LogOp()
        {
            std::cout << "Deleting logoperator" << std::endl;
        }

    private:

        INode* left_    = nullptr;

        INode* right_   = nullptr;

        LogicalOperator operator_type_ = LogicalOperator::NoType;
};

//======================================================================================//

} // end of paracl namespace

#endif