
#include "../../snowball.h"
#include "../../compiler.h"

#include <vector>
#include <string>

#include <functional>

#include <llvm/IR/Function.h>

#ifndef __SNOWBALL_STMT_CLASS_H_
#define __SNOWBALL_STMT_CLASS_H_

namespace snowball {
    class Scope;
    class FunctionNode;

    llvm::Value* create_virtual_table(llvm::Module* module, std::string p_className, Scope* p_class, std::vector<FunctionNode*> p_nodes, std::function<llvm::Function* (FunctionNode*)> p_callback);
}

#endif // __SNOWBALL_STMT_CLASS_H_
