#ifndef KALEIDO_AEXP_HPP
#define KALEIDO_AEXP_HPP

#include <vector>
#include "node/basic.hpp"
#include "node/identifier.hpp"

namespace kaleido {

class AExp;
typedef NodeList <AExp> AExpList;

class AExp: public Node {
 public:
  typedef enum {
    aexp_id, aexp_binary, aexp_unary, aexp_imm, aexp_undef,
    aexp_call, aexp_attr, aexp_slice,
  } aexp_type_t;
  typedef enum {
    aexp_add, aexp_sub, aexp_mul, aexp_div,
    aexp_pow,
    aexp_negate
  } aexp_operator_t;

  AExp();
  AExp(Identifier &id);
  AExp(int64_t ival);
  AExp(double fval);
  AExp(aexp_operator_t, AExp &node);
  AExp(aexp_type_t, AExp &, AExpList &);
  AExp(aexp_type_t, AExp &, std::string &);
  AExp(aexp_operator_t op, AExp &left, AExp &right);
  ~AExp();
  void dump(int indent);

  aexp_type_t aexp_type;
  aexp_operator_t aexp_operator;
  AExp *left = nullptr;
  AExp *right = nullptr;
  AExpList *args = nullptr;
  std::string identifier_name;
  std::string attr_name;
  bool using_int = false;
  int64_t ival;
  double fval;
};

template<typename _Tp>
class Imm: public {

    };

    }

#endif //KALEIDO_AEXP_HPP
