#include "Node.hpp"

#define DUMP

namespace paracl
{

//======================================================================================//
//====================================HELPERS===========================================//
//======================================================================================//

template <> std::string GetWord(const Operators type)
{
    switch(type)
    {
        case Operators::Asg:
            return "=";

        case Operators::Divide:
            return "/";

        case Operators::Minus:
            return "-";

        case Operators::Mult:
            return "*";

        case Operators::Plus:
            return "+";

        default:
            return "";
    }
}

//======================================================================================//

template <> std::string GetWord(const LogicalOperator type)
{
    switch(type)
    {
        case LogicalOperator::Above:
            return "&gt;";

        case LogicalOperator::Below:
            return "&lt;";

        case LogicalOperator::Eq:
            return "==";

        case LogicalOperator::EqAbove:
            return "&gt;=";

        case LogicalOperator::EqBelow:
            return "&lt;=";

        case LogicalOperator::NotEq:
            return "!=";

        default:
            return "";
    }
}

//======================================================================================//

template <> std::string GetWord(const LoopType type)
{
    switch(type)
    {
        case LoopType::If:
            return "IF";

        case LoopType::Else:
            return "ELSE";

        case LoopType::While:
            return "WHILE";

        default:
            return "";
    }
}

//======================================================================================//

template <> std::string GetWord(const InOutType type)
{
    switch(type)
    {
        case InOutType::Input:
            return "INPUT";

        case InOutType::Print:
            return "PRINT";

        default:
            return "";
    }
}

//======================================================================================//
//==================================EXECUTION===========================================//
//======================================================================================//

int BinOp::Execute() const
{
    switch(operator_type_)
    {
        case Operators::Asg:
        {
            auto left = static_cast<Variable*>(left_);

            int res = right_->Execute();

            left->SetValue(right_->Execute());

            return left->Execute();
        }

        case Operators::Plus:
            return left_->Execute() + right_->Execute();

        case Operators::Minus:
            return left_->Execute() - right_->Execute();

        case Operators::Mult:
            return left_->Execute() * right_->Execute();

        case Operators::Divide:
        {
            int right_res = right_->Execute();

            if (right_res == 0)
            {
                std::cerr << "division by zero" << std::endl;

                return 0;
            }
            
            return left_->Execute() / right_res;
        }

        default:
            std::cout << "to be continued" << std::endl;
    }

    return 0;
}

//======================================================================================//

int LogOp::Execute() const
{
    switch(operator_type_)
    {
        case LogicalOperator::Above:
            return left_->Execute() > right_->Execute();

        case LogicalOperator::Below:
            return left_->Execute() < right_->Execute();

        case LogicalOperator::Eq:
            return left_->Execute() == right_->Execute();

        case LogicalOperator::EqAbove:
            return left_->Execute() >= right_->Execute();

        case LogicalOperator::EqBelow:
            return left_->Execute() <= right_->Execute();

        case LogicalOperator::NotEq:
            return left_->Execute() != right_->Execute();

        default:
        {
            std::cerr << "Undefined logical operator " << static_cast<int>(operator_type_) << std::endl;

            return 0;
        }
    }
}

//======================================================================================//

int Scope::Execute() const
{
    if (left_)
        left_->Execute();

    if (right_)
        right_->Execute();

    return 0;
}

//======================================================================================//

int InOut::Execute() const
{
    switch(word_type_)
    {
        case InOutType::Input:
        {
            int val = 0;

            std::cin >> val;

            auto left = static_cast<Variable*>(left_);

            left->SetValue(val);

            return val;
        }

        case InOutType::Print:
        {
            int res = left_->Execute();

            std::cout << res << std::endl;

            return res;
        }

        default:
        {
            std::cerr << "Incorrect Word " << static_cast<int>(word_type_) << std::endl;

            return 0;
        }
    }
}

//======================================================================================//

int Loop::Execute() const
{
    switch(word_type_)
    {
        case LoopType::If:
        {
            auto left = static_cast<Scope*>(left_);

            if (left->GetLeft()->Execute())
                return left->GetRight()->Execute();
            
            else if (right_)
                return right_->Execute();

            return 0;
        }

        case LoopType::Else:
        {
            auto left = static_cast<Scope*>(left_);

            return left->Execute();
        }

        case LoopType::While:
        {
            while (left_->Execute())
                right_->Execute();

            return 0;
        }

        default:
        {
            std::cerr << "Incorrect Word" << static_cast<int>(word_type_) << std::endl;

            return 0;
        }
    }
}

//======================================================================================//
//========================================DUMP==========================================//
//======================================================================================//

void Digit::Dump(std::ofstream& graph_file) const
{
    #ifdef DUMP
    
        graph_file << "   \"" << this << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"yellow\",";
        
        graph_file << "   label = \" {" << value_ << "}\"];\n";
    
    #else

        std::cout << "The value is " << value_ << std::endl;

    #endif
}

//======================================================================================//

void Variable::Dump(std::ofstream& graph_file) const
{
    #ifdef DUMP
    
        graph_file << "   \"" << this << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"green\",";
        
        graph_file << "   label = \" {" << name_ << "}\"];\n";
    
    #else

        std::cout << "The name is " << name_ << "; the value is " << value_ << std::endl;

    #endif
}

//======================================================================================//

void BinOp::Dump(std::ofstream& graph_file) const
{
    #ifdef DUMP

        graph_file << "   \"" << this << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"red\"";

        graph_file << "   label = \" {" << GetWord(operator_type_) << "}\"];\n";

        if (left_)
            graph_file << "  \"" << this << "\" -> \"" << left_ << "\" [color = \"black\"];\n";

        if (right_)
            graph_file << "  \"" << this << "\" -> \"" << right_ << "\" [color = \"black\"];\n";

        if (left_)
            left_->Dump(graph_file);

        if (right_)
            right_->Dump(graph_file);

    #else

        std::cout << "The operation is " << operator_type_ << std::endl;

    #endif
}

//======================================================================================//

void LogOp::Dump(std::ofstream& graph_file) const
{
    #ifdef DUMP

        graph_file << "   \"" << this << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"aqua\"";

        graph_file << "   label = \"" << GetWord(operator_type_) << "\"];\n";

        if (left_)
            graph_file << "  \"" << this << "\" -> \"" << left_ << "\" [color = \"black\"];\n";

        if (right_)
            graph_file << "  \"" << this << "\" -> \"" << right_ << "\" [color = \"black\"];\n";

        if (left_)
            left_->Dump(graph_file);

        if (right_)
            right_->Dump(graph_file);

    #else

        std::cout << "The log operation is " << operator_type_ << std::endl;

    #endif
}

//======================================================================================//

void Scope::Dump(std::ofstream& graph_file) const
{
    #ifdef DUMP

        graph_file << "   \"" << this << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"coral1\"";

        graph_file << "   label = \" {SCOPE}\"];\n";

        if (left_)
            graph_file << "  \"" << this << "\" -> \"" << left_ << "\" [color = \"black\"];\n";

        if (right_)
            graph_file << "  \"" << this << "\" -> \"" << right_ << "\" [color = \"black\"];\n";

        if (left_)
            left_->Dump(graph_file);

        if (right_)
            right_->Dump(graph_file);

    #else

        std::cout << "Just Scope" << std::endl;

    #endif
}

//======================================================================================//

void InOut::Dump(std::ofstream& graph_file) const
{
    #ifdef DUMP

        graph_file << "   \"" << this << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"lightblue3\"";

        graph_file << "   label = \" {" << GetWord(word_type_) << "}\"];\n";

        if (left_)
            graph_file << "  \"" << this << "\" -> \"" << left_ << "\" [color = \"black\"];\n";

        if (left_)
            left_->Dump(graph_file);

    #else

        std::cout << "Just Scope" << std::endl;

    #endif
}

//======================================================================================//

void Loop::Dump(std::ofstream& graph_file) const
{
    #ifdef DUMP

        graph_file << "   \"" << this << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"palevioletred1\"";

        graph_file << "   label = \" {" << GetWord(word_type_) << "}\"];\n";

        if (left_)
            graph_file << "  \"" << this << "\" -> \"" << left_ << "\" [color = \"black\"];\n";

        if (right_)
            graph_file << "  \"" << this << "\" -> \"" << right_ << "\" [color = \"black\"];\n";

        if (left_)
            left_->Dump(graph_file);

        if (right_)
            right_->Dump(graph_file);

    #else

        std::cout << "Just Scope" << std::endl;

    #endif
}

//======================================================================================//

} // end of paracl namespace