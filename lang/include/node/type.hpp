#ifndef KALEIDO_TYPE_HPP
#define KALEIDO_TYPE_HPP

#include "node/basic.hpp"
#include <vector>

namespace kaleido {

class Type;

typedef NodeList <Type> TypeList;


class Type: public Node {
 public:
  typedef enum {
    type_int, type_double,
    type_tuple, type_array,
    type_undef
  } type_type_t;

  Type();
  Type(type_type_t type);
  Type(const TypeList &types);

  type_type_t type_type = type_undef;
  bool is_basic = false;
  Type *element_type = nullptr;
  TypeList *tuple_types = nullptr;
  void dump(int indent);
};

}

#endif //KALEIDO_TYPE_HPP
