#include <iostream>
#include "node.hpp"

using namespace std;
using namespace kaleido;

int main() {
  string name = "<anonymous>";
  auto id = Identifier(name);
  AExp aexp(id);
}