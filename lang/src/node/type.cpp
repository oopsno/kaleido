#include "node.hpp"
#include <vector>

namespace kaleido {

Type::Type() {
  node_type = type;
}

Type::Type(const type_type_t tp) {
  node_type = type;
  type_type = tp;
  is_basic = true;
}

Type::Type(const TypeList &types) {
  node_type = type;
  type_type = type_tuple;
  tuple_types = new TypeList(types);
}

void Type::dump(int indent) {
  println(indent, "<Type>");
}

}