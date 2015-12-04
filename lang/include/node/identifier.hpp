#ifndef KALEIDO_IDENTIFIER_HPP
#define KALEIDO_IDENTIFIER_HPP

#include "node/basic.hpp"

namespace kaleido {

class Identifier: public Node {
 public:
  Identifier();
  Identifier(std::string &id);
  std::string value;

  void dump(int indent);
};

}

#endif //KALEIDO_IDENTIFIER_HPP
