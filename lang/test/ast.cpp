#include "ast/arithmetic.hpp"
#include "context.hpp"

using namespace kaleido::ast;

int main() {
  codegen::Context ctx;
  Immediate<int64_t> imm_i(42);
  Immediate<double> imm_f(42.0);
  imm_f.dump(0);
  imm_f.codegen(ctx)->dump();
  imm_i.dump(0);
  imm_i.codegen(ctx)->dump();
}
