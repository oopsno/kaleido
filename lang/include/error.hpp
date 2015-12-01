#ifndef KALEIDO_ERROR_HPP
#define KALEIDO_ERROR_HPP

#include <stdexcept>
#include <string>
#include "location.hh"

namespace kaleido {

class KaleidoException: std::exception { };

class SyntaxError: KaleidoException {
  SyntaxError();
  SyntaxError(std::string& information);
  parser::location *loc = nullptr;
  std::string information;
};

}

#endif //KALEIDO_ERROR_HPP
