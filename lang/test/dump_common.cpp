#include "dump/common.hpp"

using namespace kaleido::dump;

int main() {
  print_line("RED", 0, color::RED);
  print_line("DEFAULT", 3);
  print_line("CYAN", -3, color::CYAN);
  print_line("INDENT_LIMIT", 0xFFFF);
  return 0;
}
