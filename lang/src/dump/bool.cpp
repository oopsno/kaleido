#include "ast/bool.hpp"

namespace kaleido {
namespace ast {

void Nonzero::dump(size_t indent) {
  dump::print_line("node: Nonzero", indent);
  dump::print_line("arithmetic: ", indent);
  arithmetic->dump(indent + 2);
}

void BBO::dump(size_t indent) {
  dump::print_line("node: UnaryBooleanOperate", indent);
  dump::print_line("operator: " + op::name_of(bop), indent);
  dump::print_line("lhs: ", indent);
  lhs->dump(indent + 2);
  dump::print_line("rhs: ", indent);
  rhs->dump(indent + 2);
}

void Compare::dump(size_t indent) {
  dump::print_line("node: Compare", indent);
  dump::print_line("operator: " + op::name_of(bop), indent);
  dump::print_line("lhs: ", indent);
  lhs->dump(indent + 2);
  dump::print_line("rhs: ", indent);
  rhs->dump(indent + 2);
}

void UBO::dump(size_t indent) {
  dump::print_line("node: Binarybooleanoperate", indent);
  dump::print_line("operator: " + op::name_of(uop), indent);
  dump::print_line("target: ", indent);
  target->dump(indent + 2);
}

}
}