#include "node.hpp"

namespace kaleido {

Node::Node() {
  node_type = undef;
}
Node::Node(const node_type_t tp) {
  node_type = tp;
}

void Node::dump(int indent) {
  println(indent, "<Node>");
}

void Node::println(int indent, std::string line) {
  // TODO 找个优雅的写法
  for (int i = 0; i < indent && i < 120; i++) {
    std::cout << ' ';
  }
  std::cout << line << std::endl;
}

}
