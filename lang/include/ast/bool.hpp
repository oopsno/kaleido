#ifndef KALEIDO_AST_BOOL_HPP
#define KALEIDO_AST_BOOL_HPP

#include "ast/ast.hpp"
#include "ast/arithmetic.hpp"
#include "operators.hpp"
#include "context.hpp"
#include "dump/common.hpp"
#include "codegen/type_assist.hpp"

namespace kaleido {
namespace ast {

class Boolean: public AST {
 public:
  virtual void dump(size_t indent = 0) = 0;
  virtual llvm::Value *codegen(codegen::Context &) = 0;
};

template<bool _Value>
class BooleanImm: public Boolean {
 public:
  virtual void dump(size_t indent = 0) {
    dump::print_line("node: BooleanImmediate", indent);
    if (_Value) {
      dump::print_line("value: True", indent);
    } else {
      dump::print_line("value: False", indent);
    }
  }
  virtual llvm::Value *codegen(codegen::Context &ctx) {
    llvm::Type *bool_t_ptr = codegen::ir_type_from<bool>(ctx);
    if (_Value) {
      return llvm::ConstantInt::getTrue(bool_t_ptr);
    } else {
      return llvm::ConstantInt::getFalse(bool_t_ptr);
    }
  }
};

typedef BooleanImm<true> BooleanTrue;
typedef BooleanImm<false> BooleanFalse;

class BBO: public Boolean {
 public:
  BBO();
  BBO(op::BinaryOperator, Boolean *, Boolean *);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
 private:
  op::BinaryOperator bop;
  Boolean *lhs = nullptr;
  Boolean *rhs = nullptr;
};

class Compare: public Boolean {
 public:
  Compare();
  Compare(op::BinaryOperator, Arithmetic *, Arithmetic *);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
 private:
  op::BinaryOperator bop;
  Arithmetic *lhs = nullptr;
  Arithmetic *rhs = nullptr;
};

class UBO: public Boolean {
 public:
  UBO();
  UBO(op::UnaryOperator, Boolean *);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
 private:
  op::UnaryOperator uop;
  Boolean *target = nullptr;
};

class Nonzero: public Boolean {
 public:
  Nonzero();
  Nonzero(Arithmetic *);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
 private:
  Arithmetic *arithmetic = nullptr;
};

}
}

#endif //KALEIDO_AST_BOOL_HPP
