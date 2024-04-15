#ifndef EXECUTOR_HPP_
#define EXECUTOR_HPP_

#include "AST.hpp"

namespace paracl
{

class Executor
{
    public:

        int Execute(const AST& tree) { return tree.root_->Execute(); }

    private:
};

} // end of paracl namespace

#endif