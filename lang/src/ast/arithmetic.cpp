#include "ast/arithmetic.hpp"

namespace kaleido {
namespace ast {

void Arithmetic::dump(size_t indent) {
  print_line("node: Arithmetic", indent, color::LIGHT_GRAY);
}

llvm::Value* Arithmetic::codegen(llvm::LLVMContext &) {
  return nullptr;
}

}
}