#include <stdlib.h>
#include <stdio.h>

#include "defs/cli.h"
#include "defs/dynarr.h"
#include "defs/emulator.h"


DynamicArray instructions;

#define REGISTER_COUNT 4
int registers[REGISTER_COUNT];

int main(int argc, char *argv[]) {

	FILE *output = stdout;
	int flags;
	parseArguments(argc, argv, &instructions, &output, &flags);

	EmulationResult e;

	if (flags) {
		// perform emulation steps rather than full emulation, so we can dump register data

		e = EMULATOR_STEP_DONE;
		while (e == EMULATOR_STEP_DONE) {
			e = emulationStep(&instructions.values, instructions.count, registers, REGISTER_COUNT);
			fprintf(output, "regs: ");
			for (int i = 0; i < REGISTER_COUNT; ++i) {
				fprintf(output, "[ %02d ]", registers[i]);
			}
			fprintf(output, "\n");
		}

	} else {
		// perform emulation in one go
		e = emulate( instructions.values, instructions.count, registers, REGISTER_COUNT);
	}
	

	fprintf(output, "res: %s\n", (e == EMULATION_OK) ? "success" : "fail");

	fprintf(output, "regs: ");
	for (int i = 0; i < REGISTER_COUNT; ++i) {
		fprintf(output, "[ %02d ]", registers[i]);
	}
	fprintf(output, "\n");

	fclose(output);
	exit(EXIT_SUCCESS);
}
