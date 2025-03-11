#ifndef CLI_H
#define CLI_H

#include "dynarr.h"

#include <stdio.h>


#define USAGE_MESSAGE "Usage: [-b \"bytecode\" | -f infile] [-o outfile] [-d]"

typedef enum {
	ARGPARSE_OK, ARGPARSE_ERROR,
} ArgParseResult;

ArgParseResult parseArguments(
	int argc, char *argv[],
	DynamicArray *instructions,
	FILE **output,
	int *flags
);

#endif /* CLI_H */
