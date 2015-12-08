#include "ast/operators.hpp"

static const std::string neg_("neg");
static const std::string not_("not");
static const std::string nz("NONZERO");
static const std::string unknown("Unknown");

namespace kaleido {
namespace ast {
namespace op {

static const std::string bop_table[]{
    "add", "sub", "mul", "div", "idiv", "mod", "exp",
    "and", "or", "xor",
    "gt", "ge", "eq", "le", "lt", "ne",
    "undefined_binary_operator"
};

static const std::string uop_table[]{
    "NEGATE", "NOT", "NONZERO", "UNDEFINED_UNARY_OPERATOR"
};

// Binary

const std::string &name_of(BinaryOperator op) {
  if (op >= op::UNDEFINED_BINARY_OPERATOR || op < 0) {
    return bop_table[op::UNDEFINED_BINARY_OPERATOR];
  } else {
    return bop_table[op];
  }
}

// Unary

const std::string &name_of(UnaryOperator op) {
  if (op >= op::UNDEFINED_UNARY_OPERATOR || op < 0) {
    return uop_table[UNDEFINED_UNARY_OPERATOR];
  } else {
    return uop_table[op];
  }
}

}
}
}
