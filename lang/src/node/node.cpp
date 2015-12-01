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

}
