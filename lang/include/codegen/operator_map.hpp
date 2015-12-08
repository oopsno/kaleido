#ifndef KALEIDO_CODEGEN_OPERATOR_MAP_HPP
#define KALEIDO_CODEGEN_OPERATOR_MAP_HPP

#include <llvm/IR/InstrTypes.h>
#include "ast/operators.hpp"

namespace kaleido {
namespace codegen {

using kaleido::ast::op::BinaryOperator;
using llvm::CmpInst;

CmpInst::Predicate fcmp(BinaryOperator);
CmpInst::Predicate icmp(BinaryOperator);
llvm::Instruction::BinaryOps fbinop(BinaryOperator);
llvm::Instruction::BinaryOps ibinop(BinaryOperator);



}
}


#endif //KALEIDO_OPERATOR_MAP_HPP
