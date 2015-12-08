#include "driver.hpp"
#include <iostream>

using namespace std;
using namespace kaleido;

int main() {
  parser::KaleidoDriver driver;
//  driver.parse_file("example/classic.kaleido");
  driver.parse_file("example/design.kaleido");
  driver.result->dump();
  return 0;
}