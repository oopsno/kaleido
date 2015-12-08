#include "ast/arithmetic.hpp"
#include "codegen/operator_map.hpp"

namespace kaleido {
namespace ast {

llvm::Value *VariableRef::codegen(codegen::Context &ctx) {
  // TODO deal with symbol table
  return nullptr;
}

llvm::Value *BAO::codegen(codegen::Context &ctx) {
  llvm::Value *lhs_value = lhs->codegen(ctx);
  llvm::Value *rhs_value = rhs->codegen(ctx);
  llvm::Type *balanced = codegen::rel_promote(lhs_value->getType(), rhs_value->getType());
  lhs_value = codegen::type_cast(balanced, lhs_value, ctx);
  rhs_value = codegen::type_cast(balanced, rhs_value, ctx);
  if (balanced->isIntegerTy()) {
    return ctx.builder.CreateBinOp(codegen::ibinop(bop), lhs_value, rhs_value);
  } else {
    return ctx.builder.CreateBinOp(codegen::fbinop(bop), lhs_value, rhs_value);
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
