#ifndef DRIVER_HPP_
#define DRIVER_HPP_

#include <iostream>
#include <map>
#include <FlexLexer.h>

#include "parser.hpp"
#include "location.hh"
#include "AST.hpp"

namespace yy
{

class Driver
{
    private:
    
        FlexLexer* lexer_;

    public:

        yy::location location;

        paracl::AST tree;

        paracl::Scope* current_scope;

    public:
        
        Driver(FlexLexer* lexer) : lexer_{lexer} {}

        ~Driver() { delete lexer_; };
        
        parser::token_type yylex(parser::semantic_type* yylval, parser::location_type* loc) 
        {
            parser::token_type tt = static_cast<parser::token_type>(lexer_->yylex());
            
            if (tt == yy::parser::token_type::DIGIT)
                yylval->as<int>() = std::stoi(lexer_->YYText());

            if (tt == yy::parser::token_type::VAR)
            {
                std::string var_name = lexer_->YYText();
                parser::semantic_type tmp{};
                tmp.as<std::string>() = var_name;
                yylval->swap<std::string>(tmp);
            }
            
            return tt;
        }

        bool Parse()
        {
            parser parser(this);
            
            bool res = parser.parse();

            if (tree.smart_nodes.size())
                tree.root_ = std::move(*std::prev(tree.smart_nodes.end()));

            return !res;
        }
};

} // end of yy namespace

#endif