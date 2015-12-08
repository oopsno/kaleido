#include "ast/arithmetic.hpp"
#include "ast/bool.hpp"

using namespace kaleido::ast;

int main() {
  codegen::Context ctx;
  Immediate<int64_t> *imm_i = new Immediate<int64_t>(42);
  Immediate<double> *imm_f = new Immediate<double>(42.0);
  imm_f->codegen(ctx)->dump();
  imm_i->codegen(ctx)->dump();
  BAO *addfi = new BAO(op::ADD, imm_f, imm_i);
  addfi->codegen(ctx)->dump();
  BooleanTrue().codegen(ctx)->dump();
  BooleanFalse().codegen(ctx)->dump();
  Nonzero(addfi).codegen(ctx)->dump();
  Compare *cmp_t = new Compare(op::LT, imm_i, addfi);
  Compare *cmp_f = new Compare(op::GT, imm_i, addfi);
  cmp_t->codegen(ctx)->dump();
  cmp_f->codegen(ctx)->dump();
  BBO *bbo_t = new BBO(op::XOR, cmp_f, cmp_t);
  bbo_t->codegen(ctx)->dump();
  return 0;
}
