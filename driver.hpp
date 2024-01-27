#ifndef DRIVER_HPP_
#define DRIVER_HPP_

#include <iostream>
// #include "parser.hpp"
#include <FlexLexer.h>

class Driver
{
    private:
    
        FlexLexer* lexer_;

    public:

        Driver(FlexLexer* lexer) : lexer_{lexer} {}

        bool Parse()
        {
            while (lexer_->yylex() != 0)
            {
                
            }

            return 1;
        }

};

#endif