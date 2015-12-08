#include "ast/ast.hpp"
#include "dump/common.hpp"

namespace kaleido {
namespace ast {

using namespace kaleido::dump;

void AST::dump(size_t indent) {
  print_line("node: AST", indent, color::LIGHT_GRAY);
}

AST::~AST() { }

llvm::Value *AST::codegen(codegen::Context &) {
  return nullptr;
}


const location &AST::get_reduce_location() const {
  return loc;
}

void AST::set_reduce_location(const location &loc) {
  this->loc = loc;
}

NameRef::NameRef() { }

NameRef::NameRef(std::string &name)
    : name(name) { }

llvm::Value *NameRef::codegen(codegen::Context &ctx) {
  return resolved->codegen(ctx);
}

void NameRef::dump(size_t indent) {
  if (resolved != nullptr) {
    resolved->dump(indent);
  } else {
    print_line("node: NameRef", indent);
    print_line("value: Unsolved", indent);
  }
}

void NameRef::on_found(AST *ast) {
  resolved = ast;
}


}
}