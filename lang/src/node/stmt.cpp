#include "node.hpp"

namespace kaleido {

Stmt::Stmt() : stmt(nullptr) { }

Stmt::Stmt(stmt_type_t stmt_type, Stmt *stmt) {
  this->stmt_type = stmt_type;
  wrapped = true;
  switch (stmt_type) {
#define DOWNCAST(type, cls)\
    case type: \
      this->stmt = new cls(*(cls*)stmt); \
      break
    DOWNCAST(stmt_moddef, ModDef);
    DOWNCAST(stmt_moddecl, ModDecl);
    DOWNCAST(stmt_loop, Loop);
    DOWNCAST(stmt_defun, Defun);
    DOWNCAST(stmt_import, Import);
    DOWNCAST(stmt_block, Block);
    DOWNCAST(stmt_decl, Decl);
    DOWNCAST(stmt_assign, Assign);
    DOWNCAST(stmt_aexp, RawAExp);
    DOWNCAST(stmt_ret, Return);
#undef DOWNCAST
    default:
      this->stmt = new Stmt(*stmt);
  }
}

void Stmt::dump(int indent) {
  switch (stmt_type) {
#define DOWNCAST(type, cls)\
    case type: ((cls*)(wrapped ? stmt : this))->dump(indent);  break
    DOWNCAST(stmt_moddef, ModDef);
    DOWNCAST(stmt_moddecl, ModDecl);
    DOWNCAST(stmt_loop, Loop);
    DOWNCAST(stmt_defun, Defun);
    DOWNCAST(stmt_import, Import);
    DOWNCAST(stmt_block, Block);
    DOWNCAST(stmt_decl, Decl);
    DOWNCAST(stmt_assign, Assign);
    DOWNCAST(stmt_aexp, RawAExp);
    DOWNCAST(stmt_ret, Return);
    default:
      println(indent, "<Undef Stmt>");
#undef DOWNCAST
  }
}

Block::Block() { }

Block::Block(std::vector<Stmt> &stmts)
    : stmts(stmts) {
  stmt_type = stmt_block;
}

void Block::dump(int indent) {
  println(indent, "<Block>");
  for (Stmt stmt : stmts) {
    stmt.dump(indent + 2);
  }
}

RawAExp::RawAExp() {
  stmt_type = stmt_aexp;
}


RawAExp::RawAExp(AExp &exp) {
  stmt_type = stmt_aexp;
  this->exp = exp;
}

void RawAExp::dump(int indent) {
  println(indent, "<Stmt RawAExp>");
  exp.dump(indent + 2);
}

Loop::Loop() {
  stmt_type = stmt_loop;
}

Loop::Loop(Identifier &bind, AExp &begin, AExp &end, AExp &step, Stmt *stmt)
    : bind_name(bind.value), begin(begin), end(end), step(step) {
  this->stmt = new Stmt(*stmt);
  stmt_type = stmt_loop;
}

void Loop::dump(int indent) {
  println(indent, "<Loop - Bing = \"" + bind_name + "\">");
  println(indent + 2, "<Loop - Start>");
  begin.dump(indent + 4);
  println(indent + 2, "<Loop - Step>");
  step.dump(indent + 4);
  println(indent + 2, "<Loop - End>");
  end.dump(indent + 4);
}

Assign::Assign() { }

Assign::Assign(Identifier &slot, AExp &value)
    : slot(slot.value), value(value) {
  stmt_type = stmt_assign;
}

void Assign::dump(int indent) {
  println(indent, "<Assign>");
  println(indent + 2, "<Slot \"" + slot + "\">");
  value.dump(indent + 2);
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

void Decl::dump(int indent) {
  println(indent, "<Decl>");
  type.dump(indent + 2);
  println(indent + 2, "<ID \"" + id + "\">");
}

Return::Return() {
  stmt_type = stmt_ret;
}

Return::Return(AExp &exp) {
  this->exp = exp;
  stmt_type = stmt_ret;
}

void Return::dump(int indent) {
  println(indent, "<Return>");
  exp.dump(indent + 2);
}

Defun::Defun() {
  stmt_type = stmt_defun;
}

Defun::Defun(Identifier &id, std::vector<Decl> &decls, Block &block)
    : name(id.value), decls(decls), block(block) {
  stmt_type = stmt_defun;
}

void Defun::dump(int indent) {
  println(indent, "<Defun \"" + name + "\">");
  println(indent + 2, "<ParamList>");
  for (Decl decl : decls) {
    decl.dump(indent + 4);
  }
  block.dump(indent + 4);
}

ModDecl::ModDecl() { }

ModDecl::ModDecl(std::string &name)
    : name(name) { }

void ModDecl::dump(int indent) {
  println(indent, "<ModDef \"" + name + "\"");
}

Import::Import() {
  stmt_type = stmt_import;
}

Import::Import(std::string &name)
    : name(name) {
  stmt_type = stmt_import;
}

void Import::dump(int indent) {
  println(indent, "<Import \"" + name + "\">");
}

ModDef::ModDef() {
  stmt_type = stmt_moddef;
}


ModDef::ModDef(std::vector<Stmt> &stmts)
    : stmts(stmts) {
  stmt_type = stmt_moddef;
}

ModDef::ModDef(std::string &name, std::vector<Import> &imps, std::vector<Stmt> &stmts)
    : name(name), stmts(stmts), imports(imps) {
  stmt_type = stmt_moddef;

}

void ModDef::dump(int indent) {
  println(indent, "<ModDef \"" + name + "\">");
  println(indent + 2, "<Import List>");
  for (Import imp : imports) {
    imp.dump(indent + 4);
  }
  println(indent + 2, "<Stmt List>");
  for (Stmt stmt : stmts) {
    stmt.dump(indent + 4);
  }
}

}
