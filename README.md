# KipVM
A small virtual machine I'm messing around with as a side project.

## Instruction Overview
For the sake of faster iteration, this machine will use variable length instructions, using the
following format:

> \[format] \[operation] (\[flag] \[argument])*

Instructions are stored in an array of integers, with each array index corresponding to an instruction
element.

## Instructions

### Binary Operations
Binary operations take two source registers and place the result of the operation in a third
destination register.

> \[binop] \[op] \[rA] \[rB] \[rC]
> rC = op(rA, rB)

### Immediate Operations
Immediate operations take an immediate value and a source register and places the result of the
operation back into the source register.

> \[immop] \[op] \[imm] \[rA]
> rA = op(rA, imm)
