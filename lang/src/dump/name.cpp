#include "ast/name.hpp"
#include "dump/common.hpp"

namespace kaleido {
namespace ast {

void Name::dump(size_t indent) {
  dump::print_line("node: Name", indent);
  dump::print_line("value: " + name, indent);
}

}
}