#include <iostream>
#include "cpu.h"

int main() {
  std::string filename;

  std::cout << "Enter program file: ";
  std::cin >> filename;

  loadProgram(filename);
  displayMemory();

  runCPU();

  return 0;
}
