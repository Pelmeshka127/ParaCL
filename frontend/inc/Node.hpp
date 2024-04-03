#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <fstream>

#include "INode.hpp"

namespace paracl
{

template <typename T> std::string GetWord(const T type);

std::string GetKeyWordColor(const KeyWords type);

//======================================================================================//

class Variable final : public INode
{
    public:

        Variable(const std::string name = "") 
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

        Digit(const int value = 0) 
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

        BinOp(const Operators type, INode* const left = nullptr, INode* const right = nullptr) 
            : INode(Type_t::Operation), operator_type_{type}, left_{left}, right_{right} {}

        void Dump(std::ofstream& graph_file) const override;

        ~BinOp()
        {
            std::cout << "Deleting operator" << std::endl;
        }

    private:

        INode* left_  = nullptr;

        INode* right_ = nullptr;

        Operators operator_type_ = Operators::NoType;
};

//======================================================================================//

class LogOp final : public INode
{   
    public:

        LogOp(const LogicalOperator type, INode* const left = nullptr, INode* const right = nullptr) 
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

class Scope final : public INode
{
    public:

        Scope(INode* const left = nullptr, Scope* const right = nullptr) :
            INode(Type_t::Scope), left_{left}, right_{right} {}

        void Dump(std::ofstream& graph_file) const override;

        ~Scope()
        {
            std::cout << "Deleting Scope" << std::endl;
        }

    private:

        INode* left_    = nullptr;

        Scope* right_   = nullptr;
};

//======================================================================================//

class Statement final : public INode
{
    public:

        Statement(const KeyWords type = KeyWords::NoType, INode* const left = nullptr, INode* const right = nullptr) :
            INode(Type_t::KeyWord), type_{type}, left_{left}, right_{right} {}

        void Dump(std::ofstream& graph_file) const override;

        ~Statement()
        {
            std::cout << "Deleting Statement" << std::endl;
        }


    private:

        INode* left_ = nullptr;

        INode* right_ = nullptr;

        KeyWords type_ = KeyWords::NoType;
};

//======================================================================================//

} // end of paracl namespace

#endif