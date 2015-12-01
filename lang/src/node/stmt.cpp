#include "node.hpp"

namespace kaleido {

Stmt::Stmt() : stmt(nullptr) { }

Stmt::Stmt(stmt_type_t stmt_type, Stmt *stmt)
    : stmt(stmt) { }

Block::Block() { }

Block::Block(std::vector<Stmt> &stmts)
    : stmts(stmts) {
  stmt_type = stmt_block;
}

Call::Call() { }

Call::Call(Identifier &func, std::vector<AExp> &args)
    : function_name(func.value), args(args) {
  stmt_type = stmt_call;
}

Loop::Loop() { }

Loop::Loop(Identifier &bind, AExp &begin, AExp &end, AExp &step, Stmt *stmt)
    : bind_name(bind.value), begin(begin), end(end), step(step) {
  this->stmt = stmt;
  stmt_type = stmt_loop;
}

Assign::Assign() { }

Assign::Assign(Identifier &slot, AExp &value)
    : slot(slot.value), value(value) {
  stmt_type = stmt_assign;
}

}
