#include <iostream>
#include "driver.hpp"
#include "parser.hpp"

namespace kaleido {

namespace parser {

KaleidoDriver::KaleidoDriver() {
  trace_parsing = false;
  trace_scanning = false;
  global = std::string("global");
  streamname = "air";
}

KaleidoDriver::~KaleidoDriver() { }

int KaleidoDriver::parse_file(const std::string &f) {
  file = f;
  scan_begin();
  parser::KaleidoParser parser(*this);
  parser.set_debug_level(trace_parsing);
  int res = parser.parse();
  scan_end();
  return res;
}

int KaleidoDriver::parse(const std::string &literal) {
  file = "<LITERAL>";
  parse_on_the_fly = true;
  scan_begin();
  parser::KaleidoParser parser(*this);
  parser.set_debug_level(trace_parsing);
  int res = parser.parse();
  scan_end();
  return res;
}

void KaleidoDriver::error(const parser::location &l, const std::string &m) {
  std::cerr << "[KaleidoDriver][" << l << "]: " << m << std::endl;
}

void KaleidoDriver::error(const std::string &m) {
  std::cerr << "[KaleidoDriver]: " << m << std::endl;
}

}

}


