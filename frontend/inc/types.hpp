#ifndef TYPES_HPP_
#define TYPES_HPP_

namespace paracl
{

enum Type_t {
    NoType,
    Digit,
    Variable,
    Operation,
    LogOperation,
    KeyOperation,
    Bracket,
};

enum Brackets {
    LeftBracket,
    RightBracket,
    LeftBrace,
    RightBrace,
};

enum Operators {
    Plus,
    Minus,
    Mult,
    Divide,
    Asg,
};

enum LogigalOperator {
    Above,
    EqAbove,
    Below,
    EqBelow,
    Eq,
    NotEq,
};

enum KeyWords {
    Input,
    Print,
    If,
    While,
};  

} // end of paracl namespace

#endif