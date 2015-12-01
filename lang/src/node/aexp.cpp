#include "node.hpp"

namespace kaleido {

AExp::AExp() {
  node_type = undef;
  aexp_type = aexp_undef;
}

AExp::AExp(Identifier &id) {
  node_type = aexp;
  aexp_type = aexp_id;
}

AExp::~AExp() {
  if (left != nullptr) {
    delete(left);
  }
  if (right != nullptr) {
    delete(right);
  }
}

}