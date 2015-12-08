#include "ast/rval.hpp"
#include "dump/common.hpp"

namespace kaleido {
namespace ast {

void Tuple::dump(size_t indent) {
  if (elements != nullptr) {
    dump::print_line("node: Tuple", indent);
    dump::print_line("elements:", indent);
    for (auto e : *elements) {
      e->dump(indent + 2);
    }
  } else {
    dump::print_line("node: Unit ()", indent);
  }
}

llvm::Type* Tuple::get_type() {
  return nullptr;
}

}
}
