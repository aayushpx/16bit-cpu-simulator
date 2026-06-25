#pragma once
#include <string>

// CPU state
extern int memory[256];
extern int reg[16];
extern int pc;
extern int ir;
extern int program_sz;
extern int opcode, R, X, Y, XY;

// Core functions
void loadProgram(std::string filename);
void displayMemory();
void indxDisp(int adr);
void contntDisp(int adr);

void fetch();
void opCode();
void executeInstruction();

void runCPU();

// instruction set
void LD1();
void LD2();
void LD3();
void STO();
void ADD();
void NEG();
void SHL();
void SHR();
void AND();
void OR();
void XOR();
void JMP();
void HAL();
