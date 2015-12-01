#ifndef KALEIDO_STMT_HPP
#define KALEIDO_STMT_HPP

#include "node/basic.hpp"
#include <vector>
#include <string>

namespace kaleido {

class Stmt: public Node {
 public:
  typedef enum {
    stmt_loop, stmt_call, stmt_assign, stmt_block, stmt_stmts,
    stmt_undef
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

class Call: public Stmt {
 public:
  Call();
  Call(Identifier &func, std::vector<AExp> &args);
  std::string function_name;
  std::vector<AExp> args;
};

class Assign: public Stmt {
 public:
  Assign();
  Assign(Identifier &slot, AExp &value);
  std::string slot;
  AExp value;
};

}

#endif //KALEIDO_STMT_HPP
