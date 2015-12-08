#ifndef KALEIDO_AST_RVAL_HPP
#define KALEIDO_AST_RVAL_HPP

#include "ast/ast.hpp"

namespace kaleido {
namespace ast {

class RVal: public AST {
 public:
  virtual void dump(size_t indent = 0) = 0;
  virtual llvm::Value *codegen(codegen::Context &) = 0;
  virtual llvm::Type *get_type() = 0;
};

class Tuple: public RVal {
 public:
  Tuple();
  Tuple(std::vector<AST*> *elements);
  std::vector<AST*> *elements = nullptr;
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
  virtual llvm::Type *get_type();
};

}
}

#endif //KALEIDO_RVAL_HPP
