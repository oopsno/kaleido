#ifndef KALEIDO_AST_AST_HPP
#define KALEIDO_AST_AST_HPP

#include "context.hpp"
#include "location.hh"

namespace kaleido {
namespace ast {

using kaleido::parser::location;

class AST {
 public:
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &) = 0;
  virtual ~AST();
  const location &get_reduce_location() const;
  void set_reduce_location(const location &);
 private:
  location loc;
};

}
}

#endif //KALEIDO_AST_HPP
