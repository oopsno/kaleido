#include "codegen/type_assist.hpp"

namespace kaleido {
namespace codegen {

template<>
llvm::Type *ir_type_from<double>(llvm::LLVMContext &ctx) {
  return llvm::Type::getDoubleTy(ctx);
}

template<>
llvm::Type *ir_type_from<int64_t>(llvm::LLVMContext &ctx) {
  return (llvm::Type *) llvm::Type::getInt64Ty(ctx);
}

}
}
