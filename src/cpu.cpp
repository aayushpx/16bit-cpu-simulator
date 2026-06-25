#include <iostream>
#include <iomanip>
#include "cpu.h"

int memory[256];
int reg[16];
int pc = 0;
int ir = 0;
int program_sz = 0;
int opcode, R, X, Y, XY;

void fetch() {
  /*Displays changes and status of the program.*/
  ir = memory[pc];
  std::cout << "PC:  " << std::uppercase << std::setw(2)
            << std::setfill('0') << std::hex << pc
            << "  IR:  " << std::uppercase << std::setw(4)
            << std::setfill('0') << std::hex << ir;
}

void opCode() {
  /*Decodes current instruction in IR into components.
   * Format: Op-Code|R|X|Y
   * XY is also used for instructions that use an address
   * or it be needed to display.*/

  int temp = ir;
  int mask = 0x000F; // 4-bit mask to isolate nibble

  Y = temp & mask; // extract last nibble
  temp = ir >> 12; 
  opcode = temp & mask; // extract first nibble (op-code)
  temp = ir >> 8;
  R = temp & mask; // extract second nibble (register)
  temp = ir >> 4;
  X = temp & mask; // Extract third nibble
  XY = (X << 4) | Y; // combine X and Y into one value
}
void executeInstruction() {
  /*Executes instruction based on Op-code.
   * Uses a switch statement to call corresponding instruction.*/
  switch(opcode) {

    case 1:
    LD1();
    break;

    case 2:
    LD2();
    break;

    case 3:
    LD3();
    break;

    case 4:
    STO();
    break;

    case 6:
    ADD();
    break;

    case 7:
    NEG();
    break;

    case 8:
    SHR();
    break;

    case 9:
    SHL();
    break;

    case 0xA:
    AND();
    break;

    case 0xB:
    OR();
    break;

    case 0xC:
    XOR();
    break;

    case 0xD:
    JMP();
    break;

    case 0xE:
    HAL();
    break;

    default:
    std::cout << "  UNKNOWN OPCODE\n";
    break;
  }

}

void r_format(int regist) {
  /* Displays result of instruction in format:
   * Register RX = YYYY
   * Takes value of register as parameter and prints
   * it as a 4-digit hexadecimal number.*/

  std::cout << "  Register R" << R << " = ";
  std::cout << std::uppercase << std::hex << std::setw(4) 
            << std::setfill('0') << regist;
  std::cout << std::endl;
}

void LD1() {
  /* 1RXY 
   * Load register R with XY*/ 
  reg[R] = XY;
  r_format(XY);
}

void LD2() {
  /* 20RS 
   * Load register R with value in register S*/ 
  reg[X] = reg[Y];
  R = X;
  r_format(reg[X]);
}

void LD3() {
  /* 3RXY
   * Load register R with number in MEM[XY]*/
  reg[R] = memory[XY];
  r_format(reg[R]);
}

void ADD() {
/* 6RST
 * Register R = Register S + Register T*/
  reg[R] = reg[X] + reg[Y];
  reg[R] &= 0xFFFF;
  r_format(reg[R]);
}
void JMP() {
  /* DRXY
   * If Register R is equal to Register 0, jump to instruction at
   * address XY.*/
  if (reg[R] == reg[0]) {
    pc = XY - 1;
    std::cout << "  TRUE - jump to location "
              << std::setw(2) << std::setfill('0') 
              << std::hex << XY << std::endl;
    } else {
    std::cout << "  FALSE - do not jump" << std::endl;
  }
}

void STO() {
  /* 4RXY
   * MEM[XY] = Register R*/
  memory[XY] = reg[R];
  std::cout << "  ";
  indxDisp(XY);
  std::cout << " = ";
  contntDisp(XY);
}

void NEG() {
  /* 70R0
   * ~Register*/
  reg[X] = ~reg[X] + 1; // negate (two's complement)
  reg[X] &= 0xFFFF; // mask for 16-bit output
  R = X;
  r_format(reg[R]);
}

void SHR() {
  /* 8RXY
   * Shift value in R to the right for XY bits.*/
  reg[R] >>= XY;
  reg[R] &= 0xFFFF;
  r_format(reg[R]);
}

void SHL() {
  /* 9RXY
   * Shift value in R to the left for XY bits.*/
  reg[R] <<= XY;
  reg[R] &= 0xFFFF;
  r_format(reg[R]);
}

void AND() {
  /* ARST
   * R = S AND T*/
  reg[R] = reg[X] & reg[Y];
  r_format(reg[R]); 
}

void OR() {
  /* BRST
   * R = S OR T*/
  reg[R] = reg[X] | reg[Y];
  r_format(reg[R]);
}

void XOR() {
  /* CRST
   * R = S XOR T*/
  reg[R] = reg[X] ^ reg[Y];
  r_format(reg[R]);
}

void HAL() {
  /* Halt program*/
  std::cout << "  Program halts" << std::endl;
  exit(0); 
}

void runCPU() {
  while (true) {
    fetch();
    opCode();
    executeInstruction();
    pc++;
  }
}
