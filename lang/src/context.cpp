#include <llvm/IR/IRBuilder.h>
#include "context.hpp"

namespace kaleido {
namespace codegen {

static const std::string DEFAULT_MODULE_NAME("Main");

Context::Context() : Context(DEFAULT_MODULE_NAME) { }

Context::Context(const std::string &name)
    : llvm_context(), module(name, llvm_context), builder(llvm_context) { }

}
}
