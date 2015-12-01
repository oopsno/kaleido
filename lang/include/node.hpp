#ifndef KALEIDO_NODE_HPP
#define KALEIDO_NODE_HPP

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

class Type: Node {
  Type();
};

class Identifier: Node {
 public:
  Identifier(std::string &id);
  std::string id;
};

class Decl: Node {
 public:
  Decl(Type &type, Identifier &id);
  Type type;
  Identifier id;
};

class AExp: Node {
 public:
  typedef enum {
    aexp_id, aexp_binary, aexp_unary, aexp_imm, aexp_undef
  } aexp_type_t;
  typedef enum {
    aexp_add, aexp_sub, aexp_mul, aexp_div,
    aexp_negate
  } aexp_operator_t;

  AExp();
  AExp(Identifier &id);
  ~AExp();
  static AExp add(AExp *left, AExp *right);
 private:
  aexp_type_t aexp_type;
  aexp_operator_t aexp_operator;
  AExp *left = nullptr;
  AExp *right = nullptr;
};

}

#endif //KALEIDO_NODE_HPP
