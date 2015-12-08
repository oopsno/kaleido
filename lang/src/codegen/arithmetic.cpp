#include "ast/arithmetic.hpp"

namespace kaleido {
namespace ast {

llvm::Value *VariableRef::codegen(codegen::Context &ctx) {
  // TODO deal with symbol table
  return nullptr;
}

llvm::Value *BAO::codegen(codegen::Context &ctx) {
  llvm::Value *lhs_value = lhs->codegen(ctx);
  llvm::Value *rhs_value = rhs->codegen(ctx);
  // TODO Add type check
  switch (bop) {
    case op::ADD:
      return ctx.builder.CreateFAdd(lhs_value, rhs_value);
    case op::SUB:
      return ctx.builder.CreateFSub(lhs_value, rhs_value);
    case op::MUL:
      return ctx.builder.CreateFMul(lhs_value, rhs_value);
    case op::DIV:
      return ctx.builder.CreateFDiv(lhs_value, rhs_value);
    default:
      throw std::invalid_argument("Unsupport operator: " + op::name_of(bop));
  }
}

llvm::Value *UAO::codegen(codegen::Context &ctx) {
  llvm::Value *value = arithmetic->codegen(ctx);
  switch (uop) {
    case op::NEGATE:
      if (value->getType()->isIntegerTy()) {
        return ctx.builder.CreateNeg(value);
      } else {
        return ctx.builder.CreateFNeg(value);
      }
    default:
      throw std::invalid_argument("Unsupport operator: " + op::name_of(uop));
  }
}

}
}
