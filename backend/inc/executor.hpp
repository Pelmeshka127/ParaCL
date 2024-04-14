#ifndef EXECUTOR_HPP_
#define EXECUTOR_HPP_

#include <unordered_map>
#include <string>

#include "AST.hpp"

namespace paracl
{

//======================================================================================//

class Executor
{
    public:

        void Execute(const AST& tree);

};

//======================================================================================//

} // end of paracl namespace

#endif