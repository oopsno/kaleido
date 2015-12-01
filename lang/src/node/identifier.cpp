#include "node.hpp"

namespace kaleido {

Identifier::Identifier(std::string &id) : id(id) {
  node_type = identifier;
}

}
