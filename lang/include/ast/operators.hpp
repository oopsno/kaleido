#ifndef KALEIDO_AST_OPERATORS_HPP
#define KALEIDO_AST_OPERATORS_HPP

#include <string>

namespace kaleido {
namespace ast {
namespace op {

// Binary

enum BinaryOperator {
  ADD = 0, SUB, MUL, DIV, IDIV, MOD, EXP,
  AND, OR, XOR,
  GT, GE, EQ, LE, LT, NE,
  UNDEFINED_BINARY_OPERATOR
};

const std::string &name_of(BinaryOperator);

// Unary

enum UnaryOperator {
  NEGATE = 0,
  NOT, NONZERO,
  UNDEFINED_UNARY_OPERATOR
};

const std::string &name_of(UnaryOperator);

}
}
}

#endif //KALEIDO_OPERATORS_HPP
