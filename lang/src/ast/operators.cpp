#include "ast/operators.hpp"
#include <string>

namespace kaleido {
namespace ast {
namespace op {

// Binary

const std::string &name_of(BinaryOperator op) {
  switch (op) {
    case ADD :
      return "+";
    case SUB :
      return "-";
    case MUL :
      return "*";
    case DIV :
      return "/";
    case MOD :
      return "%";
    case EXP :
      return "**";
    case AND :
      return "and";
    case OR :
      return "or";
    default:
      return "Unknown";
  }
}

// Unary

const std::string &name_of(UnaryOperator op) {
  switch (op) {
    case NOT:
      return "NOT";
    case NEGATE:
      "negate";
    default:
      return "Unknown";
  }
}

}
}
}
