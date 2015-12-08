#ifndef KALEIDO_TYPE_ASSIST_HPP
#define KALEIDO_TYPE_ASSIST_HPP

#include <llvm/IR/Type.h>
#include <stdexcept>

namespace kaleido {
namespace codegen {

template<typename _Tp>
llvm::Type *ir_type_from(codegen::Context &ctx) {
  throw std::invalid_argument(std::string("Unsupport Type: ") + typeid(_Tp).name());
}

template<>
llvm::Type *ir_type_from<double>(codegen::Context &ctx);

template<>
llvm::Type *ir_type_from<int64_t>(codegen::Context &ctx);

template<>
llvm::Type *ir_type_from<bool>(codegen::Context &ctx);

llvm::Type *rel_promote(llvm::Type *lhs, llvm::Type *rhs);

llvm::Value *type_cast(llvm::Type *, llvm::Value *, Context &);

llvm::Value *balance_type(llvm::Value *lhs, llvm::Value *rhs, llvm::BasicBlock *block, codegen::Context &ctx);

}
}

#endif //KALEIDO_TYPE_ASSIST_HPP
