#ifndef KALEIDO_DRIVER_HPP
#define KALEIDO_DRIVER_HPP

#include "location.hh"
#include "parser.hpp"
#include "context.hpp"
#include "ast.hpp"

// ... and declare it for the parser's sake.

namespace kaleido {

namespace parser {

class KaleidoDriver {
 public:
  KaleidoDriver();
  virtual ~KaleidoDriver();
  ast::AST *result;
  void scan_begin();
  void scan_end();
  bool trace_scanning;
  int parse_file(const std::string &f);
  int parse(const std::string &literal);
  std::string file;
  bool parse_on_the_fly = false;
  std::string code;
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
