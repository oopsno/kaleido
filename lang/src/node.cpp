#include "node.hpp"


namespace kaleido {

//constexpr explicit operator const char *(const node_type_t type) {
//  switch (type) {
//#define CASE_RET(x) case x: return #x
//    CASE_RET(undef);
//    CASE_RET(name);
//    CASE_RET(type);
//    CASE_RET(decl);
//    CASE_RET(aexp);
//    CASE_RET(bexp);
//    CASE_RET(loop);
//    CASE_RET(assign);
//    CASE_RET(call);
//    CASE_RET(block);
//#undef CASE_RET
//    default:
//      return "unknowm";
//  }
//}

Node::Node() {
  node_type = undef;
}
Node::Node(const node_type_t tp) {
  node_type = tp;
}

Type::Type() {
  node_type = type;
}

Identifier::Identifier(std::string &id) : id(id) {
  node_type = identifier;
}

AExp::AExp() {
  node_type = undef;
  aexp_type = aexp_undef;
}

AExp::AExp(Identifier &id) {
  node_type = aexp;
  aexp_type = aexp_id;
}

AExp::~AExp() {
  if (left != nullptr) {
    delete(left);
  }
  if (right != nullptr) {
    delete(right);
  }
}


}