#include "ast/bool.hpp"
#include "codegen/type_assist.hpp"
#include "codegen/operator_map.hpp"
#include <llvm/IR/InstrTypes.h>
#include <stdexcept>

namespace kaleido {
namespace ast {

llvm::Value *UBO::codegen(codegen::Context &ctx) {
  llvm::Value *value = target->codegen(ctx);
  switch (uop) {
    case op::NOT:
      return ctx.builder.CreateNot(value, "local_not");
    default:
      throw std::invalid_argument("Unsupport Operator in Boolean: " + op::name_of(uop));
  }
}

llvm::Value *Nonzero::codegen(codegen::Context &ctx) {
  llvm::Value *value = arithmetic->codegen(ctx);
  llvm::Type *value_type = value->getType();
  if (value_type->isIntegerTy()) {
    llvm::Value *zero = llvm::ConstantInt::get(value_type, 0, true);
    return ctx.builder.CreateICmpNE(value, zero, "local_nonzero");
  } else {
    llvm::Value *zero = llvm::ConstantFP::get(value_type, 0);
    return ctx.builder.CreateFCmpONE(value, zero, "local_fnonzero");
  }
}

llvm::Value *BBO::codegen(codegen::Context &ctx) {
  llvm::Value *lhs_value = lhs->codegen(ctx);
  llvm::Value *rhs_value = rhs->codegen(ctx);
  switch (bop) {
    case op::AND:
      return ctx.builder.CreateAnd(lhs_value, rhs_value, "local_and");
    case op::OR:
      return ctx.builder.CreateOr(lhs_value, rhs_value, "local_or");
    case op::XOR:
      return ctx.builder.CreateXor(lhs_value, rhs_value, "local_xor");
    default:
      throw std::invalid_argument("Unsupport Operator in Boolean: " + op::name_of(bop));
  }
}

llvm::Value *Compare::codegen(codegen::Context &ctx) {
  llvm::Value *lhs_value = lhs->codegen(ctx);
  llvm::Value *rhs_value = rhs->codegen(ctx);
  llvm::Type *promoted = codegen::rel_promote(lhs_value->getType(), rhs_value->getType());
  lhs_value = codegen::type_cast(promoted, lhs_value, ctx);
  rhs_value = codegen::type_cast(promoted, rhs_value, ctx);
  if (promoted->isIntegerTy()) {
    return ctx.builder.CreateICmp(codegen::icmp(bop), lhs_value, rhs_value);
  } else {
    return ctx.builder.CreateFCmp(codegen::fcmp(bop), lhs_value, rhs_value);
  }
}

}
}