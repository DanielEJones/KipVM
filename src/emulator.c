#include "../defs/emulator.h"
#include "../defs/kip_defs.h"


void do_operation(Operations op, int a, int b, int *destination) {
	switch (op) {
		case ADD: *destination = a + b; break;
		case SUB: *destination = a - b; break;
		case MUL: *destination = a * b; break;
		case LOD: *destination = a; break;
	}
}

EmulationResult emulationStep(int **instructions, int instructions_length, int *registers, int reg_count) {
	
	#define REGISTER(N) *(registers + N)
	#define FRAGMENT(N) *(ip + N)

	int *ip = *instructions;

	if (ip >= *instructions + instructions_length) {
		return EMULATION_ERROR;
	}

	switch (*ip) {
		case BINOP: {
			int rA = FRAGMENT(2), rB = FRAGMENT(3), rC = FRAGMENT(4);
			do_operation(FRAGMENT(1), REGISTER(rA), REGISTER(rB), (registers + rC));
			*instructions = ip + 5;
		} break;

		case IMMOP: {
			int imm = FRAGMENT(2), rA = FRAGMENT(3);
			do_operation(FRAGMENT(1), imm, REGISTER(rA), (registers + rA));
			*instructions = ip + 4;
		} break;

		case HALT: return EMULATION_OK;
	}

	#undef FRAGMENT
	#undef REGISTER

	return EMULATOR_STEP_DONE;
}

EmulationResult emulate(int *instructions, int instructions_length, int *registers, int reg_count) {

	#define REGISTER(N) *(registers + N)
	#define FRAGMENT(N) *(ip + N)

	int *ip = instructions;

	for (;;) {

		// Well-formed programs end with a halt, so the IP going beyond the instruction array is
		// an error. Will throw an error if there are no instructions.
		if (ip >= instructions + instructions_length) {
			return EMULATION_ERROR;
		}

		switch (*ip) {
			case BINOP: {
				int rA = FRAGMENT(2), rB = FRAGMENT(3), rC = FRAGMENT(4);
				do_operation(FRAGMENT(1), REGISTER(rA), REGISTER(rB), (registers + rC));
				ip += 5;
			} break;

			case IMMOP: {
				int imm = FRAGMENT(2), rA = FRAGMENT(3);
				do_operation(FRAGMENT(1), imm, REGISTER(rA), (registers + rA));
				ip += 4;
			} break;

			case HALT: return EMULATION_OK;
		}
	}

	#undef FRAGMENT
	#undef REGISTER
}

