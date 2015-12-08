#include "ast/bool.hpp"

namespace kaleido {
namespace ast {

Nonzero::Nonzero() { }

Nonzero::Nonzero(Arithmetic *a)
    : arithmetic(a) { }

UBO::UBO() { }

UBO::UBO(op::UnaryOperator uop, Boolean *target)
    : uop(uop), target(target) { }

BBO::BBO() { }

BBO::BBO(op::BinaryOperator bop, Boolean *lhs, Boolean *rhs)
    : bop(bop), lhs(lhs), rhs(rhs) { }

Compare::Compare() { }

Compare::Compare(op::BinaryOperator op, Arithmetic *lhs, Arithmetic *rhs)
    : bop(op), lhs(lhs), rhs(rhs) { }

}
}