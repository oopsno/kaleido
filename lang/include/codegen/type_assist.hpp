#ifndef KALEIDO_TYPE_ASSIST_HPP
#define KALEIDO_TYPE_ASSIST_HPP

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <llvm/IR/Type.h>
#include <stdexcept>

namespace kaleido {
namespace codegen {

template <typename _Tp>
llvm::Type *ir_type_from(llvm::LLVMContext &ctx) {
  throw std::invalid_argument(std::string("Unsupport Type: ") + typeid(_Tp).name());
}

}
}

#endif //KALEIDO_TYPE_ASSIST_HPP
