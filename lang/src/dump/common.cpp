#include "dump/common.hpp"
#include <iostream>

namespace kaleido {
namespace dump {

namespace color {

const char *BLACK = "\033[0;30m";
const char *RED = "\033[0;31m";
const char *GREEN = "\033[0;32m";
const char *BROWN = "\033[0;33m";
const char *BLUE = "\033[0;34m";
const char *MAGENTA = "\033[0;35m";
const char *CYAN = "\033[0;36m";
const char *LIGHT_GRAY = "\033[0;37m";
const char *DEFAULT = "\033[0m";

}

void indent_by(size_t indent) {
  for (size_t counter = 0; counter < indent && counter < INDENT_LIMIT; counter++) {
    std::cout << ' ';
  }
}

}
}
