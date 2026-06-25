#include <iostream>
#include <fstream>
#include <iomanip>
#include "cpu.h"

void loadProgram(std::string filename) {
  /*Loads .txt file, stores each line in memory[](array),
   * stores number of lines in program_sz, closes file.*/
  std::fstream inputfile;
  inputfile.open(filename.c_str(), std::fstream::in);
  if (!inputfile) {
      std::cout << "ERROR: Cannot open file.\n";
      exit(1);
  }
 
  int hexnumber, i = 0;
  while (inputfile >> std::hex >> hexnumber) {
      memory[i] = hexnumber;
      i++;
  }
  program_sz = i;
  inputfile.close();
}

// Display memory contents
void displayMemory() {
  /*Displays contents of memory[]:
   * Memory[XY] = 1234*/
  for (int i = 0; i < program_sz; i++) {
      indxDisp(i);
    std::cout << " = ";
    contntDisp(i);
  }
  std::cout << std::endl;
}

void indxDisp(int adr) {
  /*Helper function to display formatted memory address:
   * Memory[XY]*/
  std::cout << "Memory[" << std::uppercase << std::hex 
            << std::setw(2) << std::setfill('0') << adr
            << "]";
}

void contntDisp(int adr) {
  /*Helper function to display formatted contents of memory address:
   * 0000
   * 1F04*/
  std::cout << std::uppercase << std::hex << std::setw(4) 
            << std::setfill('0') << memory[adr] 
            << std::endl;
}

