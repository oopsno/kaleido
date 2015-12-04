#include "node.hpp"

namespace kaleido {

Identifier::Identifier() {
  value = std::string("<anonymous>");
  node_type = identifier;
}

Identifier::Identifier(std::string &id)
    : value(id) { node_type = identifier; }

void Identifier::dump(int indent) {
  println(indent, std::string("<ID ") + value + ">");
}

}
