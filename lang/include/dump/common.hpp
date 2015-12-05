#ifndef KALEIDO_DUMP_COMMON_HPP_HPP
#define KALEIDO_DUMP_COMMON_HPP_HPP

#include <iostream>
#include <string>
#include <cstdint>

namespace kaleido {
namespace dump {

namespace color {

extern const char *BLACK;
extern const char *RED;
extern const char *GREEN;
extern const char *BROWN;
extern const char *BLUE;
extern const char *MAGENTA;
extern const char *CYAN;
extern const char *LIGHT_GRAY;
extern const char *DEFAULT;

}

const size_t INDENT_LIMIT = 64;
void indent_by(size_t indent = 0);

template<typename _Tp>
void print_line(const _Tp &content, size_t indent, const char *color = nullptr) {
  indent_by(indent);
  if (color != nullptr) {
    std::cout << color << content << color::DEFAULT << std::endl;
  } else {
    std::cout << content << std::endl;
  }
}

}
}

#endif //KALEIDO_DUMP_COMMON_HPP_HPP
