#include "ast/arithmetic.hpp"

using namespace kaleido::ast;

int main() {
  Immediate<int64_t> imm_i(42);
  Immediate<double> imm_f(42.0);
  imm_f.dump(0);
  imm_f.codegen(llvm::getGlobalContext())->dump();
  imm_i.dump(0);
  imm_i.codegen(llvm::getGlobalContext())->dump();
}
