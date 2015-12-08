#include <ast/type.hpp>
#include "ast/statement.hpp"

namespace kaleido {
namespace ast {

Assign::Assign() { }

Assign::Assign(std::string &name, AST *value)
    : name(name), value(value) { }

Declaration::Declaration() { }

Declaration::Declaration(Type *type, Assign *assign)
    : type(type), name(assign->name), value(assign->value) { }

Declaration::Declaration(Type *type, std::string &name)
    : type(type), name(name) { }

Declaration::Declaration(Type *type, std::vector<Assign *> *init_list)
    : type(type), init_list(init_list) { }

If::If() { }

If::If(Boolean *cond, Statement *then_clause)
    : condition(cond), then_clause(then_clause) {
  else_clause = new Block();
}

If::If(Boolean *cond, Statement *then_clause, Statement *else_clause)
    : condition(cond), then_clause(then_clause), else_clause(else_clause) { }

Loop::Loop() { }

Loop::Loop(std::string &name, Arithmetic *from, Arithmetic *to, Statement *block)
    : variable(name), from_clause(from), to_clause(to), statement(block) { }

Loop::Loop(std::string &name, Arithmetic *from, Arithmetic *to, Arithmetic *step, Statement *block)
    : variable(name), from_clause(from), to_clause(to), step_clause(step), statement(block) { }

Block::Block() {
  statements = new std::vector<Statement *>();
}

Block::Block(std::vector<Statement *> *stmts)
    : statements(stmts) { }

Function::Function() { }

Function::Function(Type *rtt, std::string &name, Block *block)
    : return_type(rtt), name(name), block(block) { }

Function::Function(Type *rtt, std::string &name, std::vector<Declaration *> *decls, Block *block)
    : return_type(rtt), name(name), arguments(decls), block(block) { }

ModuleDefinition::ModuleDefinition() { }

ModuleDefinition::ModuleDefinition(std::string &name)
    : name(name) { }

ModuleImport::ModuleImport() { }

ModuleImport::ModuleImport(std::string &name)
    : name(name) { }

Expression::Expression() { }

Expression::Expression(AST *ast)
    : ast(ast) { }

Module::Module() { }

Module::Module(std::vector<Statement *> *statements)
    : statements(statements) {
  std::string defualt_name = std::string("Main");
  def = new ModuleDefinition(defualt_name);
}

Module::Module(ModuleDefinition *def, std::vector<Statement *> *statements)
    : def(def), statements(statements) { }

Return::Return() { }

Return::Return(AST *ast)
    : value(ast) { }

}
}
