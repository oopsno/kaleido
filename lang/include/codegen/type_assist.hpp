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

}
}

#endif //KALEIDO_TYPE_ASSIST_HPP
