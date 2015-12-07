#include "ast/arithmetic.hpp"

namespace kaleido {
namespace ast {

VariableRef::VariableRef() { }

VariableRef::VariableRef(std::string &name) : name(name) { }

void VariableRef::dump(size_t indent) {
  print_line("node: VariableRef", indent);
  print_line("value: " + name, indent);
}

BAO::BAO() { }

BAO::BAO(op::BinaryOperator bop, Arithmetic *lhs, Arithmetic *rhs)
    : bop(bop), lhs(lhs), rhs(rhs) { }

BAO::~BAO() {
  if (lhs != nullptr)
    delete (lhs);
  if (rhs != nullptr)
    delete (rhs);
}

UAO::UAO() { }

UAO::UAO(op::UnaryOperator uop, Arithmetic *a)
    : uop(uop), arithmetic(a) { }

UAO::~UAO() {
  if (arithmetic != nullptr)
    delete (arithmetic);
}

}
}