#include "driver.hpp"
#include <iostream>

using namespace std;
using namespace kaleido;

int main() {
  parser::KaleidoDriver driver;
  driver.parse_file("/tmp/test.kaleido");
  driver.result.dump();
  return 0;
}