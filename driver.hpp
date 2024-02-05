#ifndef DRIVER_HPP_
#define DRIVER_HPP_

#include <iostream>
#include "parser.hpp"
#include <FlexLexer.h>

namespace yy
{

class Driver
{
    private:
    
        FlexLexer* lexer_;

    public:

        Driver(FlexLexer* lexer) : lexer_{lexer} {}

        parser::token_type yylex(parser::semantic_type* yylval) 
        {
            parser::token_type tt = static_cast<parser::token_type>(lexer_->yylex());
            
            if (tt == yy::parser::token_type::DIGIT)
                yylval->as<int>() = std::stoi(lexer_->YYText());
            
            return tt;
        }

        bool Parse()
        {
            // while (lexer_->yylex() != 0)
            // {
                
            // }

            parser parser(this);
            bool res = parser.parse();
            return !res;

            return 1;
        }

};

} // end of yy namespace

#endif