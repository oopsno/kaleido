#include "node.hpp"

namespace kaleido {

AExp::AExp() {
  node_type = undef;
  aexp_type = aexp_undef;
}

AExp::AExp(Identifier &id) {
  node_type = aexp;
  aexp_type = aexp_id;
  identifier_name = id.value;
}

AExp::AExp(int64_t ival) {
  node_type = aexp;
  aexp_type = aexp_imm;
  using_int = true;
  this->ival = ival;
}

AExp::AExp(double fval) {
  node_type = aexp;
  aexp_type = aexp_imm;
  this->fval = fval;
}

AExp::AExp(aexp_operator_t op, AExp &node) {
  node_type = aexp;
  aexp_type = aexp_unary;
  aexp_operator = op;
  this->left = new AExp(node);
}

AExp::AExp(aexp_operator_t op, AExp &left, AExp &right) {
  node_type = aexp;
  aexp_type = aexp_binary;
  aexp_operator = op;
  this->left = new AExp(left);
  this->right = new AExp(right);
}

AExp::AExp(Identifier &func, std::vector<AExp> &args) {
  node_type = aexp;
  aexp_type = aexp_call;
  function_name = func.value;
  args = args;
}

const char * dump_aexp_type(AExp::aexp_operator_t t) {
  switch (t) {
    case AExp::aexp_add:
      return "+";
    case AExp::aexp_sub:
    case AExp::aexp_negate:
      return "-";
    case AExp::aexp_mul:
      return "*";
    case AExp::aexp_div:
      return "/";
  }
  return "";
}

void AExp::dump(int indent) {
  switch (aexp_type) {
    case aexp_id:
      println(indent, "<AExp ID \"" + identifier_name + "\">");
      break;
    case aexp_imm:
      println(indent, "<Imm " + (using_int ? std::to_string(ival) : std::to_string(fval)) + ">");
      break;
    case aexp_unary:
      println(indent, std::string("<AExp '") + dump_aexp_type(aexp_operator) + "'>");
      left->dump(indent + 2);
      break;
    case aexp_binary:
      println(indent, std::string("<AExp '") + dump_aexp_type(aexp_operator) + "'>");
      left->dump(indent + 2);
      right->dump(indent + 2);
      break;
    case aexp_call:
      println(indent, "<AExp Call \"" + function_name + "\">");
      for (AExp aexp : args) {
        aexp.dump(indent + 2);
      }
      break;
    default:
      println(indent, "<Undefined AExp>");
      break;
  }
}

AExp::~AExp() {
  // TODO 重写一个安全的拷贝构造函数
  if (left != nullptr) {
//    delete (left);
  }
  if (right != nullptr) {
//    delete (right);
  }
}

}