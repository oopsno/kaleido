#include "ast/type.hpp"
#include "context.hpp"
#include <vector>

using namespace kaleido::ast;
using namespace kaleido::codegen;
using std::vector;

int main() {
  Context ctx;
  Type *i32 = new Int32();
  Type *f64 = new Double();
  Pointer *i32_ptr = new Pointer(i32);
  Array *f64_vec = new Array(f64, 42);
  vector<Type *> *fields = new vector<Type *>();
  fields->push_back(i32);
  fields->push_back(f64);
  fields->push_back(i32_ptr);
  fields->push_back(f64_vec);
  Structure *mixup = new Structure(fields);
  Array *struct_arr = new Array(mixup, 314);
  vector<Type *> *test_fields = new vector<Type *>(*fields);
  test_fields->push_back(mixup);
  test_fields->push_back(struct_arr);
  for(auto field : *test_fields) {
    field->gentype(ctx)->dump();
  }
  return 0;
}