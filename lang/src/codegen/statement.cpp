#include "ast/statement.hpp"
#include <llvm/IR/Verifier.h>

namespace kaleido {
namespace ast {

llvm::Value *Function::codegen(codegen::Context &ctx) {
  std::vector<llvm::Type *> arg_type_list = std::vector<llvm::Type *>();
  for (Declaration *arg_decl : *arguments) {
    arg_type_list.push_back(arg_decl->type->gentype(ctx));
  }
  llvm::FunctionType *ft = llvm::FunctionType::get(return_type->gentype(ctx), arg_type_list, false);
  llvm::Function *function = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, name, &ctx.module);
  auto iter = arguments->begin();
  for (auto &arg : function->args()) {
    arg.setName((*iter)->name);
    iter++;
  }
  llvm::BasicBlock *bb = llvm::BasicBlock::Create(ctx.llvm_context, "entry", function);
  ctx.builder.SetInsertPoint(bb);
  ctx.builder.CreateRet(block->codegen(ctx));
  llvm::verifyFunction(*function);
  return function;
}

llvm::Value *If::codegen(codegen::Context &ctx) {
  llvm::Value *cond = condition->codegen(ctx);
  llvm::Value *bool_true = BooleanTrue().codegen(ctx);
  cond = ctx.builder.CreateICmpEQ(cond, bool_true, "if-cond");
  llvm::Function *function = ctx.builder.GetInsertBlock()->getParent();
  llvm::BasicBlock *then_bb = llvm::BasicBlock::Create(ctx.llvm_context, "then", function);
  llvm::BasicBlock *else_bb = llvm::BasicBlock::Create(ctx.llvm_context, "else");
  llvm::BasicBlock *merge_bb = llvm::BasicBlock::Create(ctx.llvm_context, "if");
  ctx.builder.CreateCondBr(cond, then_bb, else_bb);
  ctx.builder.SetInsertPoint(then_bb);
  llvm::Value *then_value = then_clause->codegen(ctx);
  ctx.builder.CreateBr(merge_bb);
  then_bb = ctx.builder.GetInsertBlock();
  function->getBasicBlockList().push_back(else_bb);
  ctx.builder.SetInsertPoint(else_bb);
  // TODO Fix empty else_clause
  llvm::Value *else_value = else_clause->codegen(ctx);
  ctx.builder.CreateBr(merge_bb);
  else_bb = ctx.builder.GetInsertBlock();
  function->getBasicBlockList().push_back(merge_bb);
  ctx.builder.SetInsertPoint(merge_bb);
  llvm::Type *phi_type = codegen::rel_promote(then_value->getType(), else_value->getType());
  llvm::PHINode *phi = ctx.builder.CreatePHI(phi_type, 2, "iftmp");
  phi->addIncoming(then_value, then_bb);
  phi->addIncoming(else_value, else_bb);
  return phi;
}

llvm::Value *Loop::codegen(codegen::Context &ctx) {
  return nullptr;
}

llvm::Value *Assign::codegen(codegen::Context &ctx) {
  return nullptr;
}

llvm::Value *Declaration::codegen(codegen::Context &ctx) {
  return nullptr;
}

llvm::Value *Block::codegen(codegen::Context &ctx) {
  for (auto stmt : *statements) {
    stmt->codegen(ctx);
  }
  return ctx.builder.GetInsertBlock();
}

llvm::Value *ModuleImport::codegen(codegen::Context &ctx) {
  return nullptr;
}

llvm::Value *ModuleDefinition::codegen(codegen::Context &ctx) {
  return nullptr;
}

llvm::Value *Expression::codegen(codegen::Context &ctx) {
  return ast->codegen(ctx);
}

llvm::Value *Module::codegen(codegen::Context &ctx) {
  for (auto stmt : *statements) {
    stmt->codegen(ctx);
  }
  return ctx.builder.GetInsertBlock();
}

llvm::Value *Return::codegen(codegen::Context &ctx) {
  return ctx.builder.CreateRet(value->codegen(ctx));
}

}
}