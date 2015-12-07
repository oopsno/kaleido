#ifndef KALEIDO_AST_OPERATORS_HPP
#define KALEIDO_AST_OPERATORS_HPP

#include <string>

namespace kaleido {
namespace ast {
namespace op {

// Binary

enum BinaryOperator {
  ADD, SUB, MUL, DIV, IDIV, MOD, EXP, AND, OR, XOR, UNDEFINED_BINARY_OPERATOR
};

const std::string &name_of(BinaryOperator);

// Unary

enum UnaryOperator {
  NOT, NEGATE, UNDEFINED_UNARY_OPERATOR
};

const std::string &name_of(UnaryOperator);

}
}
}

#endif //KALEIDO_OPERATORS_HPP
