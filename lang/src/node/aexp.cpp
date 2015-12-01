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