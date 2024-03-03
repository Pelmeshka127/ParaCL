#include "Node.hpp"

#define DUMP

namespace paracl
{

//======================================================================================//

template <> std::string GetSign(const Operators type)
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

template <> std::string GetSign(const LogicalOperator type)
{
    switch(type)
    {
        case LogicalOperator::Above:
            return ">";

        case LogicalOperator::Below:
            return "<";

        case LogicalOperator::Eq:
            return "==";

        case LogicalOperator::EqAbove:
            return ">=";

        case LogicalOperator::EqBelow:
            return "<=";

        case LogicalOperator::NotEq:
            return "!=";

        default:
            return "";
    }
}

//======================================================================================//

void Digit::Dump(std::ofstream& graph_file) const
{
    #ifdef DUMP
    
        graph_file << "   \"" << this << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"yellow\",";
        
        graph_file << "   label = \" {DIGIT | Value = " << value_ << "}\"];\n";
    
    #else

        std::cout << "The value is " << value_ << std::endl;

    #endif
}

//======================================================================================//

void Variable::Dump(std::ofstream& graph_file) const
{
    #ifdef DUMP
    
        graph_file << "   \"" << this << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"green\",";
        
        graph_file << "   label = \" {VARIABLE | Name = " << name_ << "}\"];\n";
    
    #else

        std::cout << "The name is " << name_ << "; the value is " << value_ << std::endl;

    #endif
}

//======================================================================================//

void BinOp::Dump(std::ofstream& graph_file) const
{
    #ifdef DUMP

        graph_file << "   \"" << this << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"red\"";

        graph_file << "   label = \" {OPERATOR | " << GetSign<Operators>(operator_type_) << "}\"];\n";

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

        graph_file << "   label = \" {LOGICAL OPERATOR | " << GetSign<LogicalOperator>(operator_type_) << "}\"];\n";

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

} // end of paracl namespace