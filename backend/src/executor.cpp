#include "executor.hpp"

namespace paracl
{

//======================================================================================//

void Executor::Execute(const AST& tree)
{
    tree.Dump();

    tree.root_->Execute();
}

//======================================================================================//

} // end of paracl namespace