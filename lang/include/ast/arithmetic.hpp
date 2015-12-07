#ifndef KALEIDO_AST_ARITHMETIC_HPP
#define KALEIDO_AST_ARITHMETIC_HPP

#include "ast/ast.hpp"
#include "ast/operators.hpp"
#include "dump/common.hpp"
#include "codegen/type_assist.hpp"
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <llvm/IR/Constants.h>

namespace kaleido {
namespace ast {

using namespace kaleido::dump;
using namespace kaleido;

class Arithmetic: public AST {
 public:
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &) = 0;
};

template<typename _Tp>
class Immediate: public Arithmetic {
 public:
  typedef _Tp element_t;
  Immediate();
  Immediate(element_t val) : value(val) { }
  element_t value;

  virtual void dump(size_t indent) {
    print_line("node: Imm", indent);
    print_line(std::string("element_t: ") + typeid(element_t).name(), indent);
    print_line("value: " + std::to_string(value), indent);
  }

  virtual llvm::Value *codegen(codegen::Context &ctx) {
    llvm::Type *type = codegen::ir_type_from<element_t>(ctx);
    if (std::is_integral<element_t>::value) {
      return llvm::ConstantInt::get(type, value, true);
    } else if (std::is_floating_point<element_t>::value) {
      return llvm::ConstantFP::get(type, value);
    } else {
      throw std::invalid_argument(std::string("Unsupport Type: ") + typeid(_Tp).name());
    }
  };
};

class VariableRef: public Arithmetic {
 public:
  VariableRef();
  VariableRef(std::string &);
  std::string name;
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
};

class BAO: public Arithmetic {
 public:
  BAO();
  BAO(op::BinaryOperator, Arithmetic *, Arithmetic *);
  ~BAO();
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
 private:
  op::BinaryOperator bop = op::UNDEFINED_BINARY_OPERATOR;
  Arithmetic *lhs;
  Arithmetic *rhs;
};
typedef BAO BinaryArithmeticOperate;

class UAO: public Arithmetic {
 public:
  UAO();
  UAO(op::UnaryOperator, Arithmetic *);
  ~UAO();
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
 private:
  op::UnaryOperator uop = op::UNDEFINED_UNARY_OPERATOR;
  Arithmetic *arithmetic;
};
typedef UAO UnaryArithmeticOperate;

}
}

#endif //KALEIDO_AST_ARITHMETIC_HPP
