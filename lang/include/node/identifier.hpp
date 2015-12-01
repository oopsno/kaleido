#ifndef KALEIDO_IDENTIFIER_HPP
#define KALEIDO_IDENTIFIER_HPP

#include "node/basic.hpp"

namespace kaleido {

class Identifier: Node {
 public:
  Identifier(std::string &id);
  std::string id;
};

}

#endif //KALEIDO_IDENTIFIER_HPP
