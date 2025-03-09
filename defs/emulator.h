#ifndef EMULATOR_H
#define EMULATOR_H

typedef enum {
	EMULATION_OK, EMULATION_ERROR,
} EmulationResult;

EmulationResult emulate(int *instructions, int instruction_length, int *registers, int reg_count);

#endif /* EMULATOR_H */
