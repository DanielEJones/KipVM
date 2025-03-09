#include <stdlib.h>
#include <stdio.h>

#include "defs/emulator.h"
#include "defs/kip_defs.h"


int instructions[] = {
	IMMOP, ADD, 4, 0,
	IMMOP, ADD, 3, 1,
	BINOP, MUL, 0, 1, 2,
	HALT
};

#define REG_COUNT 4
int registers[REG_COUNT];

int main(int argc, char *argv[]) {

	EmulationResult e = emulate(instructions, sizeof(instructions) / sizeof(int), registers, REG_COUNT);

	if (e == EMULATION_ERROR) {
		fprintf(stderr, "There was an error running the program\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < REG_COUNT; ++i) {
		printf("[ %02d ]", registers[i]);
	}

	printf("\n");

	exit(EXIT_SUCCESS);
}
