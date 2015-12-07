#include "ast/ast.hpp"
#include "dump/common.hpp"

namespace kaleido {
namespace ast {

using namespace kaleido::dump;

void AST::dump(size_t indent) {
  print_line("node: AST", indent, color::LIGHT_GRAY);
}

AST::~AST() { }

llvm::Value *AST::codegen(llvm::LLVMContext &) {
  return nullptr;
}


const location &AST::get_reduce_location() const {
  return loc;
}

void AST::set_reduce_location(const location &loc) {
  this->loc = loc;
}

}
}