#ifndef TYPES_HPP_
#define TYPES_HPP_

namespace paracl
{

enum class Type_t {
    NoType,
    Digit,
    Variable,
    Operation,
    LogOperation,
    InOutOperation,
    LoopOperation,
    Scope,
    Bracket,
};

enum class Brackets {
    LeftBracket,
    RightBracket,
    LeftBrace,
    RightBrace,
};

enum class Operators {
    NoType,
    Plus,
    Minus,
    Mult,
    Divide,
    Asg
};

enum class LogicalOperator {
    NoType,
    Above,
    EqAbove,
    Below,
    EqBelow,
    Eq,
    NotEq,
};

enum class InOutType {
    NoType,
    Input,
    Print,
};  

enum class LoopType {
    NoType,
    If,
    Else,
    While,
};

} // end of paracl namespace

#endif