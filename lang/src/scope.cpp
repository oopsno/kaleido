#include "scope.hpp"
#include "stdio.h"
#include <algorithm>

namespace kaleido {

ScopeError::ScopeError(const Scope *scope, std::string name) :
    scope(scope), failed_name(name) {
}

Scope::Scope() {
  Scope(nullptr);
}

Scope::Scope(Scope *parent) {
  std::string name = gen_random_name(this);
  Scope(name, parent);
}

Scope::Scope(const std::string &name) {
  Scope(name, nullptr);
}

Scope::Scope(const std::string &name, Scope *parent) :
    name(name), parent(parent) {
}

Node &Scope::lookup(const std::string &name) {
  map_t::iterator iter = current.find(name);
  if (iter != current.end()) {
    return iter->second;
  } else {
    if (parent != nullptr) {
      return parent->lookup(name);
    } else {
      throw ScopeError(this, name);
    }
  }
}

void Scope::set(const std::string &name, const Node &node) {
  current[name] = node;
}

std::string Scope::gen_random_name(void *address) {
  char *name;
  asprintf(&name, "<Anonymous Scope at %p>", address);
  if (name != nullptr) {
    return name;
  } else {
    return "<Anonymous Scope - MEMERROR>";
  }
}

}
