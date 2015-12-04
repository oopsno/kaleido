#ifndef KALEIDO_BASIC_HPP
#define KALEIDO_BASIC_HPP

#include <vector>
#include <type_traits>
#include "scope.hpp"
#include "context.hpp"

namespace kaleido {

class Node {
 public:
  typedef enum {
    undef, identifier, aexp, expr, loop, assign, type, decl,
    call, mod_import, mod_decl, mod_def, block, float_literal, node_list
  } node_type_t;

  node_type_t node_type;
  Node();
  Node(const node_type_t type);
  virtual void dump(int indent = 0);
  void println(int indent, std::string line);
};

template<typename _Tp>
class NodeList: public Node {
  static_assert(std::is_base_of<Node, _Tp>::value, "Node a => NodeList a");
 public:
  typedef _Tp element_t;
  typedef NodeList<_Tp> list_t;

  NodeList() : Node(node_list) { };
  NodeList(const element_t &elem) : NodeList() {
    elements.push_back(elem);
  }
  std::vector<element_t> elements;

  const list_t &push(const element_t &elem) {
    elements.push_back(elem);
    return *this;
  }

  typename std::vector<_Tp>::iterator begin() {
    return elements.begin();
  }

  typename std::vector<_Tp>::iterator end() {
    return elements.end();
  }

  void dump(int indent) {
    println(indent, "<NodeList>");
    for (Node &elem : elements) {
      elem.dump(indent + 2);
    }
  }
};

}

#endif //KALEIDO_BASIC_HPP
