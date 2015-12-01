#ifndef KALEIDO_AEXP_HPP
#define KALEIDO_AEXP_HPP

#include "node/basic.hpp"
#include "node/identifier.hpp"

namespace kaleido {

class AExp: Node {
 public:
  typedef enum {
    aexp_id, aexp_binary, aexp_unary, aexp_imm, aexp_undef
  } aexp_type_t;
  typedef enum {
    aexp_add, aexp_sub, aexp_mul, aexp_div,
    aexp_negate
  } aexp_operator_t;

  AExp();
  AExp(Identifier &id);
  ~AExp();
  static AExp add(AExp *left, AExp *right);
 private:
  aexp_type_t aexp_type;
  aexp_operator_t aexp_operator;
  AExp *left = nullptr;
  AExp *right = nullptr;
};

}

#endif //KALEIDO_AEXP_HPP
