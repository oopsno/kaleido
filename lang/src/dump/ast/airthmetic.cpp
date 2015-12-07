#include "ast/arithmetic.hpp"
#include "dump/common.hpp"


namespace kaleido {
namespace ast {

using namespace kaleido::dump;

void Arithmetic::dump(size_t indent) {
  print_line("<Undefined Arithmetic>", indent, color::RED);
}

}
}