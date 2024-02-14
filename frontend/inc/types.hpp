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
    KeyOperation,
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
    Asg,
};

enum class LogigalOperator {
    Above,
    EqAbove,
    Below,
    EqBelow,
    Eq,
    NotEq,
};

enum class KeyWords {
    Input,
    Print,
    If,
    While,
};  

} // end of paracl namespace

#endif