#ifndef KALEIDO_DECL_HPP
#define KALEIDO_DECL_HPP

#include "node/basic.hpp"
#include "node/type.hpp"

namespace kaleido {

class Decl: public Node {
 public:
  Decl(Type &type, Identifier &id);
  Type type;
  Identifier id;
};

}

#endif //KALEIDO_DECL_HPP
