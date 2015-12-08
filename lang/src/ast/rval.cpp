#include "ast/rval.hpp"

namespace kaleido {
namespace ast {

Tuple::Tuple() { }

Tuple::Tuple(std::vector<AST *> *elements)
    : elements(elements) { }

}
}
