#include "ast/type.hpp"
#include <algorithm>

namespace kaleido {
namespace ast {

Type::~Type() { }

Array::Array() { }

Array::Array(Type *element_type, size_t length)
    : element_type(element_type), length(length) { }

llvm::Type *Array::gentype(codegen::Context &ctx) const {
  llvm::Type *llvm_element_type = element_type->gentype(ctx);
  if (element_type->is_primitive()) {
    return llvm::VectorType::get(llvm_element_type, length);
  } else {
    return llvm::ArrayType::get(llvm_element_type, length);
  }
}

std::string Array::to_string() const {
  if (is_primitive()) {
    return "< " + element_type->to_string() + " x " + std::to_string(length) + " >";
  } else {
    return "[ " + element_type->to_string() + " x " + std::to_string(length) + " ]";
  }
}

bool Array::is_primitive() const {
  return element_type->is_primitive();
}

Structure::Structure() { }

Structure::Structure(std::vector<Type *> *fields)
    : fields(fields) { }

llvm::Type *Structure::gentype(codegen::Context &ctx) const {
  std::vector<llvm::Type *> *llvm_fields = new std::vector<llvm::Type *>();
  for (auto field : *fields) {
    llvm_fields->push_back(field->gentype(ctx));
  }
  return llvm::StructType::get(ctx.llvm_context, llvm::ArrayRef<llvm::Type *>(*llvm_fields));
}

std::string Structure::to_string() const {
  std::string head = "{ ";
  for (auto field : *fields) {
    head += field->to_string();
    head += ", ";
  }
  head += " }";
  return head;
}

bool Structure::is_primitive() const {
  return false;
}

Pointer::Pointer() { }

Pointer::Pointer(Type *target)
    : target_type(target) { }

llvm::Type *Pointer::gentype(codegen::Context &ctx) const {
  return llvm::PointerType::get(target_type->gentype(ctx), 0);
}

std::string Pointer::to_string() const {
  return target_type->to_string() + "*";
}

bool Pointer::is_primitive() const {
  return true;
}

TypeRef::TypeRef() { }

TypeRef::TypeRef(std::string &name)
    : name(name) { }

bool TypeRef::is_primitive() const {
  return resolved and resolved->is_primitive();
}

llvm::Type *TypeRef::gentype(codegen::Context &ctx) const {
  return resolved->gentype(ctx);
}

std::string TypeRef::to_string() const {
  return resolved->to_string();
}

void TypeRef::on_found(Type *type) {
  resolved = type;
}

}
}