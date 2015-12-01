#ifndef KALEIDO_DRIVER_HPP
#define KALEIDO_DRIVER_HPP

#include "location.hh"
#include "scope.hpp"
#include "node.hpp"
#include "parser.hpp"

// ... and declare it for the parser's sake.

namespace kaleido {

namespace parser {

class KaleidoDriver {
 public:
  KaleidoDriver();
  virtual ~KaleidoDriver();
  Scope global;
  Node result;
  void scan_begin();
  void scan_end();
  bool trace_scanning;
  int parse(const std::string &f);
  std::string file;
  bool trace_parsing;  // Error handling.
  void error(const parser::location &l, const std::string &m);
  void error(const std::string &m);
  std::string streamname;
};

}

}

# define YY_DECL kaleido::parser::KaleidoParser::symbol_type yylex (kaleido::parser::KaleidoDriver& driver)
YY_DECL;
#endif //KALEIDO_DRIVER_HPP
