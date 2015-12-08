#include "context.hpp"
#include "codegen/type_assist.hpp"
#include <llvm/IR/Instructions.h>
#include <stdexcept>

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

template<>
llvm::Type *ir_type_from<bool>(codegen::Context &ctx) {
  return (llvm::Type *) llvm::Type::getInt1Ty(ctx.llvm_context);
}

static llvm::Type *rel_promote_i(llvm::Type *lhs, llvm::Type *rhs) {
  uint32_t lhs_bitwidth = lhs->getIntegerBitWidth();
  uint32_t rhs_bitwidth = lhs->getIntegerBitWidth();
  if (lhs_bitwidth >= rhs_bitwidth) {
    return lhs;
  } else {
    return rhs;
  }
}

static llvm::Type *rel_promote_f(llvm::Type *lhs, llvm::Type *rhs) {
  if (lhs->isDoubleTy()) {
    return lhs;
  }
  if (rhs->isDoubleTy()) {
    return rhs;
  }
  if (lhs->isFloatTy() && rhs->isFloatTy()) {
    return lhs;
  }
  throw std::invalid_argument("Unknown cast");
}

llvm::Type *rel_promote(llvm::Type *lhs, llvm::Type *rhs) {
  // TODO fix type-cast
  if (lhs->isIntegerTy() && rhs->isIntegerTy()) {
    return rel_promote_i(lhs, rhs);
  } else {
    return rel_promote_f(lhs, rhs);
  }
}

static llvm::Value *type_cast_si_to_si(llvm::Type *dest, llvm::Value *value, Context &ctx) {
  if (dest->getIntegerBitWidth() > value->getType()->getIntegerBitWidth()) {
    return ctx.builder.CreateCast(llvm::Instruction::SExt, value, dest);
  } else {
    return ctx.builder.CreateCast(llvm::Instruction::Trunc, value, dest);
  }
}

static llvm::Value *type_cast_si_to_fp(llvm::Type *dest, llvm::Value *value, Context &ctx) {
  return ctx.builder.CreateCast(llvm::Instruction::SIToFP, value, dest);
}

static llvm::Value *type_cast_fp_to_si(llvm::Type *dest, llvm::Value *value, Context &ctx) {
  return ctx.builder.CreateCast(llvm::Instruction::FPToSI, value, dest);
}

static llvm::Value *type_cast_fp_to_fp(llvm::Type *dest, llvm::Value *value, Context &ctx) {
  if (dest->getPrimitiveSizeInBits() > value->getType()->getPrimitiveSizeInBits()) {
    return ctx.builder.CreateCast(llvm::Instruction::FPExt, value, dest);
  } else {
    return ctx.builder.CreateCast(llvm::Instruction::FPTrunc, value, dest);
  }
}

llvm::Value *type_cast(llvm::Type *dest, llvm::Value *value, Context &ctx) {
  llvm::Type *value_type = value->getType();
  if (value_type != dest) {
    if (dest->isIntegerTy()) {
      if (value_type->isIntegerTy()) {
        return type_cast_si_to_si(dest, value, ctx);
      } else {
        return type_cast_fp_to_si(dest, value, ctx);
      }
    } else {
      if (value_type->isIntegerTy()) {
        return type_cast_si_to_fp(dest, value, ctx);
      } else {
        return type_cast_fp_to_fp(dest, value, ctx);
      }
    }
  } else{
    return value;
  }
}

}
}
