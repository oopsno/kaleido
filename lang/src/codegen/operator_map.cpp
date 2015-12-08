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

