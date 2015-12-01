#ifndef KALEIDO_BASIC_HPP
#define KALEIDO_BASIC_HPP

#include "scope.hpp"
#include "context.hpp"

namespace kaleido {

typedef enum {
  undef, identifier, aexp, bexp, loop, assign, type, decl,
  call, mod_import, mod_decl, block, float_literal
} node_type_t;

//constexpr operator const char *(const node_type_t);

template<typename tp>
struct auto_node_type {
  const static node_type_t value = undef;
};

template<>
struct auto_node_type<std::string> {
  const static node_type_t value = identifier;
};

template<>
struct auto_node_type<double> {
  const static node_type_t value = float_literal;
};

class Node {
 public:
  node_type_t node_type;
  Node();
  Node(const node_type_t type);
};

}

#endif //KALEIDO_BASIC_HPP
