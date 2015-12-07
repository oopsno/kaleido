#include "ast/name.hpp"
#include "dump/common.hpp"

namespace kaleido {
namespace ast {

llvm::Value *Name::codegen(codegen::Context &) {
  return nullptr;
}

}
}