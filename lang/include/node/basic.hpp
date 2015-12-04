#ifndef KALEIDO_BASIC_HPP
#define KALEIDO_BASIC_HPP

#include "scope.hpp"
#include "context.hpp"

namespace kaleido {

class Node {
 public:
  typedef enum {
    undef, identifier, aexp, bexp, loop, assign, type, decl,
    call, mod_import, mod_decl, block, float_literal
  } node_type_t;

  node_type_t node_type;
  Node();
  Node(const node_type_t type);
  virtual void dump(int indent = 0);
  void println(int indent, std::string line);
};

}

#endif //KALEIDO_BASIC_HPP
