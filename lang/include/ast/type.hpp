#ifndef KALEIDO_AST_TYPE_HPP
#define KALEIDO_AST_TYPE_HPP

#include <llvm/IR/Type.h>
#include <stdexcept>
#include <context.hpp>
#include <vector>

namespace kaleido {
namespace ast {

class Type {
 public:
  virtual std::string to_string() const = 0;
  virtual llvm::Type *gentype(codegen::Context &ctx) const = 0;
  virtual bool is_primitive() const = 0;
};

template<int bits>
class PrimitiveInteger: public Type {
 public:
  virtual std::string to_string() const {
    return "i" + std::to_string(bits);
  }
  virtual llvm::Type *gentype(codegen::Context &ctx) const {
    switch (bits) {
      case 1:
        return llvm::Type::getInt1Ty(ctx.llvm_context);
      case 8:
        return llvm::Type::getInt8Ty(ctx.llvm_context);
      case 16:
        return llvm::Type::getInt16Ty(ctx.llvm_context);
      case 32:
        return llvm::Type::getInt32Ty(ctx.llvm_context);
      case 64:
        return llvm::Type::getInt64Ty(ctx.llvm_context);
      default:
        throw std::out_of_range("PrimitiveInteger: " + to_string() + "out of range");
    }
  }
  virtual bool is_primitive() const {
    return true;
  }
};

template<int bits>
class PrimitiveFloat: public Type {
 public:
  virtual std::string to_string() const {
    return "f" + std::to_string(bits);
  }
  virtual llvm::Type *gentype(codegen::Context &ctx) const {
    switch (bits) {
      case 16:
        return llvm::Type::getHalfTy(ctx.llvm_context);
      case 32:
        return llvm::Type::getFloatTy(ctx.llvm_context);
      case 64:
        return llvm::Type::getDoubleTy(ctx.llvm_context);
      default:
        throw std::out_of_range("PrimitiveInteger: " + to_string() + "out of range");
    }
  }
  virtual bool is_primitive() const {
    return true;
  }
};

typedef PrimitiveFloat<16> Half;
typedef PrimitiveFloat<32> Float;
typedef PrimitiveFloat<64> Double;
typedef PrimitiveInteger<1> Int1;
typedef PrimitiveInteger<8> Int8;
typedef PrimitiveInteger<16> Int16;
typedef PrimitiveInteger<32> Int32;
typedef PrimitiveInteger<64> Int64;

class Array: public Type {
 public:
  Array();
  Array(Type *, size_t);
  virtual std::string to_string() const;
  virtual llvm::Type *gentype(codegen::Context &ctx) const;
  virtual bool is_primitive() const;
 private:
  Type *element_type = nullptr;
  size_t length = 0;
};

class Structure: public Type {
 public:
  Structure();
  Structure(std::vector<Type *> *);
  virtual std::string to_string() const;
  virtual llvm::Type *gentype(codegen::Context &ctx) const;
  virtual bool is_primitive() const;
 private:
  std::vector<Type *> *fields = nullptr;
};

class Pointer: public Type {
 public:
  Pointer();
  Pointer(Type *);
  virtual std::string to_string() const;
  virtual llvm::Type *gentype(codegen::Context &ctx) const;
  virtual bool is_primitive() const;
 private:
  Type *target_type = nullptr;
};

class TypeRef: public Type {
 public:
  TypeRef();
  TypeRef(std::string &name);
  virtual std::string to_string() const;
  virtual llvm::Type *gentype(codegen::Context &ctx) const;
  virtual bool is_primitive() const;
  void on_found(Type *type);
 private:
  std::string name;
  Type *resolved = nullptr;
};

}
}

#endif //KALEIDO_TYPE_HPP
