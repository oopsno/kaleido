#ifndef KALEIDO_CONTEXT_HPP
#define KALEIDO_CONTEXT_HPP

#include <string>
#include <map>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

namespace kaleido {
namespace codegen {

class Context {
 public:
  Context();
  Context(const std::string &name);
  llvm::LLVMContext llvm_context;
  llvm::IRBuilder<> builder;
  llvm::Module module;
  std::map<std::string, llvm::Value *> symbol_table;
};

}
}


#endif //KALEIDO_CONTEXT_HPP
