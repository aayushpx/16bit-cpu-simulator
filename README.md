# 16-bit CPU Simulator (Custom ISA)

A C++ simulation of a simple 16-bit CPU that executes a custom instruction set architecture (ISA). The simulator models core processor components including registers, memory, a program counter, and an instruction register, and executes machine code step-by-step using a fetch–decode–execute cycle.

---

## Overview

This project implements a basic virtual CPU capable of executing programs written in a custom 16-bit instruction format. It demonstrates fundamental systems programming concepts such as:

- Instruction decoding
- Register-based computation
- Memory addressing
- Control flow (jumps and halting)
- CPU execution cycle simulation

---

## Architecture

The simulated CPU consists of:

- **Memory (256 words)**: stores instructions and data
- **Registers (16 total)**: general-purpose computation registers
- **Program Counter (PC)**: tracks current instruction
- **Instruction Register (IR)**: holds current instruction

Execution follows a standard loop:

> Fetch → Decode → Execute → Increment PC

---

## Instruction Set Architecture (ISA)

Each instruction is 16 bits (4 hexadecimal digits):

- First hex digit = opcode
- Remaining digits = registers or memory addresses

| Instruction | Description |
|------------|-------------|
| 1RXY | Load register R with immediate value XY |
| 20RS | Load register R with value from register S |
| 3RXY | Load register R from memory address XY |
| 4RXY | Store register R into memory address XY |
| 5RST | Floating-point addition (not required for execution) |
| 6RST | Integer addition of registers S and T into R |
| 70R0 | Negate register R |
| 8RXY | Shift register R right by XY bits |
| 9RXY | Shift register R left by XY bits |
| ARST | Bitwise AND of registers S and T into R |
| BRST | Bitwise OR of registers S and T into R |
| CRST | Bitwise XOR of registers S and T into R |
| DRXY | Conditional jump if R == R0 |
| E000 | Halt execution |

---

## How It Works

1. A program file containing hexadecimal instructions is loaded into memory
2. The CPU begins executing from memory[0]
3. Each cycle:
   - Fetch instruction into IR
   - Decode opcode and operands
   - Execute instruction
   - Update PC
4. Execution continues until HALT instruction (E000)

---

## Build & Run

### Compile

```bash
g++ src/*.cpp -Iinclude -o cpu
Run
./cpu programs/prog1.txt
```

Example

```
100A
1107
3209
6312
D307
43FF
E000
```

### Output

The simulator displays:

- Program Counter (PC)
- Instruction Register (IR)
- Register updates
- Memory updates
- Control flow (jumps / halts)


### Purpose

This project was built to understand:

- How CPUs execute instructions internally
- How machine code is decoded and processed
- Low-level memory and register operations
- Systems-level programming in C++

#### Notes
- The ISA is simplified for educational purposes
- Floating-point instruction (5RST) is defined but not implemented
- Program assumes valid machine code input
