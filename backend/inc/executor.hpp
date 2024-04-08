#ifndef EXECUTOR_HPP_
#define EXECUTOR_HPP_

#include <unordered_map>
#include <string>

#include "AST.hpp"

namespace paracl
{

class SymTab
{
    public:

        void WrightVar(const std::string& var, const int value) { vars[var] = value; }

        int GetVar(const std::string& var) const { return vars.at(var); }

        std::unordered_map<std::string, int> vars{};

    private:
};

//======================================================================================//

class Executor
{
    public:

        void Execute(const AST& tree);

    private:

        std::unordered_map<std::string, int> symtab;

};

//======================================================================================//

} // end of paracl namespace

#endif