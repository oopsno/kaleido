#ifndef KALEIDO_STMT_HPP
#define KALEIDO_STMT_HPP

#include "node/basic.hpp"
#include <vector>
#include <string>

namespace kaleido {

class Stmt: public Node {
 public:
  typedef enum {
    stmt_loop, stmt_aexp, stmt_assign, stmt_block, stmt_stmts,
    stmt_undef, stmt_decl, stmt_defun, stmt_stmt
  } stmt_type_t;
  stmt_type_t stmt_type = stmt_undef;

  Stmt();
  Stmt(stmt_type_t stmt_type, Stmt *stmt);
  Stmt *stmt = nullptr;
};

class Block: public Stmt {
 public:
  Block();
  Block(std::vector<Stmt> &stmts);
  std::vector<Stmt> stmts;
};

class Loop: public Stmt {
 public:
  Loop();
  Loop(Identifier &bind, AExp &begin, AExp &end, AExp &step, Stmt *stmt);
  std::string bind_name;
  AExp begin;
  AExp end;
  AExp step;
};

class RawAExp: public Stmt {
 public:
  RawAExp();
  RawAExp(AExp &exp);
  AExp exp;
};

class Assign: public Stmt {
 public:
  Assign();
  Assign(Identifier &slot, AExp &value);
  std::string slot;
  AExp value;
};

class Decl: public Stmt {
 public:
  Decl();
  Decl(Type &type, Identifier &id);
  Type type;
  std::string id;
};

class Defun: public Stmt {
 public:
  Defun();
  Defun(Identifier &id, std::vector<Decl> &decls, Block &block);
  std::string name;
  std::vector<Decl> decls;
  Block block;
};

class ModDecl: public Stmt {
 public:
  ModDecl();
  ModDecl(std::string &name);
  std::string name;
};

class Import: public Stmt {
 public:
  Import();
  Import(std::string &name);
  std::string name;
};

class ModDef: public Stmt {
 public:
  ModDef();
  ModDef(std::vector<Stmt>&);
  ModDef(std::string&, std::vector<Import>&, std::vector<Stmt>&);
  std::vector<Stmt> stmts;
  std::vector<Import> imports;
  std::string name;
};

}

#endif //KALEIDO_STMT_HPP
