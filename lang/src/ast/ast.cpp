#include "ast/ast.hpp"
#include "dump/common.hpp"

namespace kaleido {
namespace ast {

using namespace kaleido::dump;

void AST::dump(size_t indent) {
  print_line("node: AST", indent, color::LIGHT_GRAY);
}

llvm::Value* AST::codegen(llvm::LLVMContext &) {
  return nullptr;
}

//const location &get_reduce_location() const {
//  return location;
//}
//
//void set_reduce_location(const location & loc) {
//  location = loc;
//}

}
}