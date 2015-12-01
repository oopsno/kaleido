#include "node.hpp"

namespace kaleido {

AExp::AExp() {
  node_type = undef;
  aexp_type = aexp_undef;
}

AExp::AExp(Identifier &id) {
  node_type = aexp;
  aexp_type = aexp_id;
  identifier_name = new std::string(id.value);
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

AExp::~AExp() {
  if (left != nullptr) {
    delete (left);
  }
  if (right != nullptr) {
    delete (right);
  }
  if (identifier_name != nullptr) {
    delete (identifier_name);
  }
}

}