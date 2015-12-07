#include "context.hpp"
#include "codegen/type_assist.hpp"

namespace kaleido {
namespace codegen {

template<>
llvm::Type *ir_type_from<double>(codegen::Context &ctx) {
  return llvm::Type::getDoubleTy(ctx.llvm_context);
}

template<>
llvm::Type *ir_type_from<int64_t>(codegen::Context &ctx) {
  return (llvm::Type *) llvm::Type::getInt64Ty(ctx.llvm_context);
}

}
}
