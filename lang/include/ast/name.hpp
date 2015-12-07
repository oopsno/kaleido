#ifndef KALEIDO_AST_NAME_HPP
#define KALEIDO_AST_NAME_HPP

#include "ast/ast.hpp"

namespace kaleido {
namespace ast {

class Name: public AST {
 public:
  Name();
  Name(std::string &);
  std::string name;
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
};

}
}


#endif //KALEIDO_NAME_HPP
