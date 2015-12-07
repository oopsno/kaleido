#include "ast/arithmetic.hpp"

namespace kaleido {
namespace ast {

llvm::Value *BAO::codegen(codegen::Context &ctx) {
  llvm::Value *lhs_value = lhs->codegen(ctx);
  llvm::Value *rhs_value = rhs->codegen(ctx);
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
  llvm::Value *target = arithmetic->codegen(ctx);
  switch (uop) {
    case op::NEGATE:
      return ctx.builder.CreateFNeg(target);
    default:
      throw std::invalid_argument("Unsupport operator: " + op::name_of(uop));
  }
}

}
}
