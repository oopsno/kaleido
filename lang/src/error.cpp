#include "error.hpp"

namespace kaleido {

SyntaxError::SyntaxError() { }

SyntaxError::SyntaxError(std::string &information) {
  this->information = information;
}

}

