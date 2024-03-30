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

        std::map<std::string, int> vars_;

        paracl::Scope* current_scope;

    public:
        
        Driver(FlexLexer* lexer) : lexer_{lexer} {}

        ~Driver() { delete lexer_; };
        
        parser::token_type yylex(parser::semantic_type* yylval, yy::location* loc) 
        {
            parser::token_type tt = static_cast<parser::token_type>(lexer_->yylex());
            
            if (tt == yy::parser::token_type::DIGIT)
                yylval->as<int>() = std::stoi(lexer_->YYText());
            
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