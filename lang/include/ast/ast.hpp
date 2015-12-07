#ifndef KALEIDO_AST_AST_HPP
#define KALEIDO_AST_AST_HPP

#include "llvm/IR/Verifier.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
//#include "location.hh"

namespace kaleido {
namespace ast {

//using kaleido::parser::location;

class AST {
 public:
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(llvm::LLVMContext &) = 0;
//  const location &get_reduce_location() const;
//  void set_reduce_location(const location &);
// private:
//  location loc;
};

}
}

#endif //KALEIDO_AST_HPP
