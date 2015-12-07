#include "ast/name.hpp"
#include "dump/common.hpp"

namespace kaleido {
namespace ast {

Name::Name() { }

Name::Name(std::string &name) : name(name) { }

}
}