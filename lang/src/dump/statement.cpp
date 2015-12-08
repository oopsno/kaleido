#include "ast/statement.hpp"
#include "dump/common.hpp"

namespace kaleido {
namespace ast {

void Assign::dump(size_t indent) {
  print_line("node: Assign", indent);
  print_line("name: " + name, indent);
  print_line("value:", indent);
  value->dump(indent + 2);
}

void Declaration::dump(size_t indent) {
  print_line("node: Declaration", indent);
  print_line("type: " + type->to_string(), indent);
  print_line("name: " + name, indent);
  if (value != nullptr) {
    print_line("value: ", indent);
    value->dump(indent + 2);
  }
}

void If::dump(size_t indent) {
  print_line("node: If", indent);
  print_line("condition:", indent);
  condition->dump(indent + 2);
  print_line("then-clause:", indent);
  then_clause->dump(indent + 2);
  if (else_clause != nullptr) {
    print_line("else-clause:", indent);
    else_clause->dump(indent + 2);
  }
}

void Loop::dump(size_t indent) {
  print_line("node: Loop", indent);
  print_line("variable: " + variable, indent);
  print_line("from:", indent);
  from_clause->dump(indent + 2);
  print_line("to:", indent);
  to_clause->dump(indent + 2);
  print_line("step:", indent);
  step_clause->dump(indent + 2);
  print_line("statement:", indent);
  statement->dump(indent + 2);
}

void Block::dump(size_t indent) {
  print_line("node: Block", indent);
  print_line("statements:", indent);
  for (auto stmt : *statements) {
    stmt->dump(indent + 2);
  }
}

void Function::dump(size_t indent) {
  print_line("node: Function", indent);
  print_line("return_type: " + return_type->to_string(), indent);
  print_line("arguments:", indent);
  for (auto arg : *arguments) {
    arg->dump(indent + 2);
  }
  print_line("block:", indent);
  block->dump(indent);
}

void ModuleDefinition::dump(size_t indent) {
  print_line("node: ModuleDefinition", indent);
  print_line("name: " + name, indent);
}

void ModuleImport::dump(size_t indent) {
  print_line("node: ModuleImport", indent);
  print_line("name: " + name, indent);
}

void Expression::dump(size_t indent) {
  ast->dump(indent);
}

void Module::dump(size_t indent) {
  print_line("node: Module", indent);
  print_line("name: " + def->name, indent);
  print_line("statements:", indent);
  for (auto stmt : *statements) {
    stmt->dump(indent + 2);
  }
}

void Return::dump(size_t indent) {
  print_line("node: Return", indent);
  print_line("value:", indent);
  value->dump(indent + 2);
}

}
}
