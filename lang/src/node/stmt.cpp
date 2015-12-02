#include "node.hpp"

namespace kaleido {

Stmt::Stmt() : stmt(nullptr) { }

Stmt::Stmt(stmt_type_t stmt_type, Stmt *stmt) {
  this->stmt_type = stmt_type;
  this->stmt = new Stmt(*stmt);
}

Block::Block() { }

Block::Block(std::vector<Stmt> &stmts)
    : stmts(stmts) {
  stmt_type = stmt_block;
}

RawAExp::RawAExp() {
  stmt_type = stmt_aexp;
}

RawAExp::RawAExp(AExp &exp) {
  stmt_type = stmt_aexp;
  this->exp = exp;
}

Loop::Loop() { }

Loop::Loop(Identifier &bind, AExp &begin, AExp &end, AExp &step, Stmt *stmt)
    : bind_name(bind.value), begin(begin), end(end), step(step) {
  this->stmt = new Stmt(*stmt);
  stmt_type = stmt_loop;
}

Assign::Assign() { }

Assign::Assign(Identifier &slot, AExp &value)
    : slot(slot.value), value(value) {
  stmt_type = stmt_assign;
}

Decl::Decl() {
  node_type = decl;
  stmt_type = stmt_decl;
}

Decl::Decl(Type &type, Identifier &id)
    : type(type), id(id.value) {
  node_type = decl;
  stmt_type = stmt_decl;
}

Defun::Defun() {
  stmt_type = stmt_defun;
}

Defun::Defun(Identifier &id, std::vector<Decl> &decls, Block &block)
    : name(id.value), decls(decls), block(block) {
  stmt_type = stmt_defun;
}

ModDecl::ModDecl() { }

ModDecl::ModDecl(std::string &name)
    : name(name) { }

Import::Import() {
  stmt_type = stmt_import;
}

Import::Import(std::string &name)
    : name(name) {
  stmt_type = stmt_import;
}

ModDef::ModDef() {
  stmt_type = stmt_modef;
}

ModDef::ModDef(std::vector<Stmt> &stmts)
    : stmts(stmts) {
  stmt_type = stmt_modef;
}

ModDef::ModDef(std::string &name, std::vector<Import> &imps, std::vector<Stmt> &stmts)
    : name(name), stmts(stmts), imports(imps) {
  stmt_type = stmt_modef;

}

}
