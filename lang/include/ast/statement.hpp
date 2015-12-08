#ifndef KALEIDO_AST_STATEMENT_HPP
#define KALEIDO_AST_STATEMENT_HPP

#include "ast/type.hpp"
#include "ast/ast.hpp"
#include "ast/bool.hpp"

namespace kaleido {
namespace ast {

class Statement: public AST {
 public:
  virtual void dump(size_t indent = 0) = 0;
  virtual llvm::Value *codegen(codegen::Context &) = 0;
};

class Assign: public Statement {
 public:
  Assign();
  Assign(std::string &name, AST *value);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
  std::string name;
  AST *value = nullptr;
};

class Declaration: public Statement {
 public:
  Declaration();
  Declaration(Type *, std::string &);
  Declaration(Type *, Assign *);
  Declaration(Type *, std::vector<Assign *> *);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
  Type *type = nullptr;
  std::string name;
  AST *value = nullptr;
  std::vector<Assign *> *init_list = nullptr;
};

class If: public Statement {
 public:
  If();
  If(Boolean *, Statement *);
  If(Boolean *, Statement *, Statement *);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
 private:
  Boolean *condition = nullptr;
  Statement *then_clause = nullptr;
  Statement *else_clause = nullptr;
};

class Loop: public Statement {
 public:
  Loop();
  Loop(std::string &, Arithmetic *, Arithmetic *, Statement *);
  Loop(std::string &, Arithmetic *, Arithmetic *, Arithmetic *, Statement *);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
 private:
  std::string variable;
  Arithmetic *from_clause;
  Arithmetic *to_clause;
  Arithmetic *step_clause = nullptr;
  Statement *statement = nullptr;
};

class Block: public Statement {
 public:
  Block();
  Block(std::vector<Statement *> *);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
 private:
  std::vector<Statement *> *statements;
};

class Function: public Statement {
 public:
  Function();
  Function(Type *, std::string &, std::vector<Declaration *> *, Block *);
  Function(Type *, std::string &, Block *);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
 private:
  Type *return_type;
  std::string name;
  std::vector<Declaration *> *arguments = nullptr;
  Block *block;
};

class ModuleDefinition: public Statement {
 public:
  ModuleDefinition();
  ModuleDefinition(std::string &);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
  std::string name;
};

class ModuleImport: public Statement {
 public:
  ModuleImport();
  ModuleImport(std::string &);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
  std::string name;
};

class Expression: public Statement {
 public:
  Expression();
  Expression(AST *ast);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
  AST *ast = nullptr;
};

class Module: public AST {
 public:
  Module();
  Module(std::vector<Statement *> *statements);
  Module(ModuleDefinition *def, std::vector<Statement *> *statements);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
  ModuleDefinition *def;
  std::vector<Statement *> *statements;
};

class Return: public Statement {
 public:
  Return();
  Return(AST *ast);
  virtual void dump(size_t indent = 0);
  virtual llvm::Value *codegen(codegen::Context &);
 private:
  AST *value;

};

}
}

#endif //KALEIDO_STATEMENT_HPP
