#include "Node.hpp"

#define DUMP

namespace paracl
{

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

template <> std::string GetWord(const KeyWords type)
{
    switch(type)
    {
        case KeyWords::If:
            return "IF";

        case KeyWords::Else:
            return "ELSE";

        case KeyWords::While:
            return "WHILE";

        case KeyWords::Input:
            return "INPUT";

        case KeyWords::Print:
            return "PRINT";

        default:
            return "";
    }
}

//======================================================================================//

std::string GetKeyWordColor(const KeyWords type)
{
    switch(type)
    {
        case KeyWords::If:
            return "palevioletred1";

        case KeyWords::Else:
            return "palevioletred1";

        case KeyWords::While:
            return "palevioletred1";

        case KeyWords::Input:
            return "khaki1";

        case KeyWords::Print:
            return "khaki1";

        default:
            return "";
    }
}

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

void Statement::Dump(std::ofstream& graph_file) const
{
    #ifdef DUMP

        graph_file << "   \"" << this << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"" << GetKeyWordColor(type_) << "\"";

        graph_file << "   label = \" {" << GetWord(type_) << "}\"];\n";

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