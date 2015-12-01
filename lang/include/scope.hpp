#ifndef KALEIDO_SCOPE_HPP
#define KALEIDO_SCOPE_HPP

#include <map>
#include <string>
#include "node.hpp"
#include "error.hpp"

namespace kaleido {

class Node;

class Scope {
 public:
  typedef std::map<std::string, Node> map_t;
  Scope();
  Scope(Scope *parent);
  Scope(const std::string &name);
  Scope(const std::string &name, Scope *parent);
  Node &lookup(const std::string &name);
  void set(const std::string &name, const Node &node);
 private:
  static std::string gen_random_name(void * address);
  std::string name;
  map_t current;
  Scope *parent;
};

class ScopeError : KaleidoException {
 public:
  ScopeError(const Scope * scope, std::string name);
 private:
  const Scope * scope;
  std::string failed_name;
};


}


#endif //KALEIDO_SCOPE_HPP
