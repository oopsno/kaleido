#ifndef KALEIDO_AEXP_HPP
#define KALEIDO_AEXP_HPP

#include <vector>
#include "node/basic.hpp"
#include "node/identifier.hpp"

namespace kaleido {

class AExp: public Node {
 public:
  typedef enum {
    aexp_id, aexp_binary, aexp_unary, aexp_imm, aexp_undef, aexp_call
  } aexp_type_t;
  typedef enum {
    aexp_add, aexp_sub, aexp_mul, aexp_div,
    aexp_negate
  } aexp_operator_t;

  AExp();
  AExp(Identifier &id);
  AExp(int64_t ival);
  AExp(double fval);
  AExp(aexp_operator_t, AExp &node);
  AExp(aexp_operator_t op, AExp &left, AExp &right);
  AExp(Identifier &func, std::vector<AExp> &args);
  ~AExp();
  void dump(int indent);

  aexp_type_t aexp_type;
  aexp_operator_t aexp_operator;
  AExp *left = nullptr;
  AExp *right = nullptr;
  std::string identifier_name;
  std::string function_name;
  std::vector<AExp> args;
  bool using_int = false;
  int64_t ival;
  double fval;
};

}

#endif //KALEIDO_AEXP_HPP
