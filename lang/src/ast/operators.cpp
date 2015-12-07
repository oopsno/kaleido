#include "ast/operators.hpp"
#include <string>

static const std::string add("+");
static const std::string sub("-");
static const std::string mul("*");
static const std::string div("/");
static const std::string idiv("//");
static const std::string mod("&");
static const std::string exp("^");
static const std::string and_("and");
static const std::string or_("or");
static const std::string xor_("xor");
static const std::string neg_("neg");
static const std::string not_("not");
static const std::string unknown("Unknown");

namespace kaleido {
namespace ast {
namespace op {

// Binary

const std::string &name_of(BinaryOperator op) {
  switch (op) {
    case ADD :
      return add;
    case SUB :
      return sub;
    case MUL :
      return mul;
    case DIV :
      return div;
    case IDIV:
      return idiv;
    case MOD :
      return mod;
    case EXP :
      return exp;
    case AND :
      return and_;
    case OR :
      return or_;
    case XOR:
      return xor_;
    default:
      return unknown;
  }
}

// Unary

const std::string &name_of(UnaryOperator op) {
  switch (op) {
    case NOT:
      return not_;
    case NEGATE:
      return neg_;
    default:
      return unknown;
  }
}

}
}
}
