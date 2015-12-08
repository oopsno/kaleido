#include "ast/arithmetic.hpp"
#include "dump/common.hpp"


namespace kaleido {
namespace ast {

using namespace kaleido::dump;

void Arithmetic::dump(size_t indent) {
  print_line("<Undefined Arithmetic>", indent, color::RED);
}

void BAO::dump(size_t indent) {
  print_line("node: BinaryArithmeticOperate", indent);
  print_line("operator:" + op::name_of(bop), indent);
  print_line("lhs:", indent);
  lhs->dump(indent + 2);
  print_line("rhs:", indent);
  rhs->dump(indent + 2);
}

void UAO::dump(size_t indent) {
  print_line("node: UnaryArithmeticOperate", indent);
  print_line("operator:" + op::name_of(uop), indent);
  print_line("value: ", indent);
  arithmetic->dump(indent);
}

void Call::dump(size_t indent) {
  print_line("node: Call", indent);
  print_line("functoin: " + name, indent);
  print_line("arguments:", indent);
  for (auto arg : *argument) {
    arg->dump(indent + 2);
  }
}

}
}