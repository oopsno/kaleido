#include "codegen/operator_map.hpp"
#include "ast/operators.hpp"
#include <map>

namespace kaleido {
namespace codegen {

static CmpInst::Predicate fcmp_table[] = {
    CmpInst::Predicate::FCMP_OGT,
    CmpInst::Predicate::FCMP_OGE,
    CmpInst::Predicate::FCMP_OEQ,
    CmpInst::Predicate::FCMP_OLE,
    CmpInst::Predicate::FCMP_OLT,
    CmpInst::Predicate::FCMP_ONE,
};

static CmpInst::Predicate icmp_table[] = {
    CmpInst::Predicate::ICMP_SGT,
    CmpInst::Predicate::ICMP_SGE,
    CmpInst::Predicate::ICMP_EQ,
    CmpInst::Predicate::ICMP_SLE,
    CmpInst::Predicate::ICMP_SLT,
    CmpInst::Predicate::ICMP_NE,
};

static llvm::Instruction::BinaryOps fbinop_table[]{
    llvm::Instruction::BinaryOps::FAdd,
    llvm::Instruction::BinaryOps::FSub,
    llvm::Instruction::BinaryOps::FMul,
    llvm::Instruction::BinaryOps::FDiv,
    llvm::Instruction::BinaryOps::FDiv,
    llvm::Instruction::BinaryOps::FRem
};

static llvm::Instruction::BinaryOps ibinop_table[]{
    llvm::Instruction::BinaryOps::Add,
    llvm::Instruction::BinaryOps::Sub,
    llvm::Instruction::BinaryOps::Mul,
    llvm::Instruction::BinaryOps::SDiv,
    llvm::Instruction::BinaryOps::SDiv,
    llvm::Instruction::BinaryOps::SRem
};

llvm::Instruction::BinaryOps fbinop(BinaryOperator op) {
  if (op < ast::op::ADD || op > ast::op::MOD) {
    throw std::out_of_range("BinaryOperator to CmpInst::Predicate: Out of range");
  } else {
    return fbinop_table[op - ast::op::ADD];
  }
}
llvm::Instruction::BinaryOps ibinop(BinaryOperator op) {
  if (op < ast::op::ADD || op > ast::op::MOD) {
    throw std::out_of_range("BinaryOperator to CmpInst::Predicate: Out of range");
  } else {
    return ibinop_table[op - ast::op::ADD];
  }
}

CmpInst::Predicate fcmp(BinaryOperator op) {
  if (op < ast::op::GT || op > ast::op::NE) {
    throw std::out_of_range("BinaryOperator to CmpInst::Predicate: Out of range");
  }
  return fcmp_table[op - ast::op::GT];
}

CmpInst::Predicate icmp(BinaryOperator op) {
  if (op < ast::op::GT || op > ast::op::NE) {
    throw std::out_of_range("BinaryOperator to CmpInst::Predicate: Out of range");
  }
  return icmp_table[op - ast::op::GT];
}

}
}

