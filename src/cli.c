#include "../defs/cli.h"

#include <stdarg.h>
#include <string.h>
#include <stdio.h>


int CLI_HAS_HAD_ERROR = 0;

static void parseError(const char *process, const char *format, ...) {
	CLI_HAS_HAD_ERROR = 1;

	va_list args;
	va_start(args, format);

	// slice the first two characters "./" with the + 2
	fprintf(stderr, "[%s] Error parsing arguments: ", process + 2);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n\t%s\n", USAGE_MESSAGE);

	va_end(args);
}

static int matchFlag(const char *value, const char *match) {
	if (value == NULL) {
		return 0;
	}
	return strncmp(value, match, strlen(match)) == 0;
}

static char *nextArg(int argc, char **argv, char ***current, int can_fail) {
	if (*current + 1 > argv + argc) {
		if (can_fail) {
			parseError(argv[0], "Not enough arguments");
		}
		return NULL;
	}

	char *val = **current;
	*current += 1;

	return val;
}

ArgParseResult parseArguments(int argc, char **argv, DynamicArray *instructions, FILE **output, int *flags) {

	char **arglist = argv + 1;

	#define NEXT_ARG(F) nextArg(argc, argv, &arglist, F); if (CLI_HAS_HAD_ERROR) { return ARGPARSE_ERROR; }

	for (;;) {
		const char *current = NEXT_ARG(0);

		if (matchFlag(current, "-b")) {
			const char *bytecode = NEXT_ARG(1);

			int num;
			while (sscanf(bytecode, "%d", &num) == 1) {
				append(instructions, num);

				while (*bytecode != ' ' && *bytecode != '\0') bytecode++;
				if (*bytecode == ' ') bytecode++;
			}

		} else if (matchFlag(current, "-f")) {
			const char *filepath = NEXT_ARG(1);
			FILE *source = fopen(filepath, "r");

			int num;
			while (fscanf(source, "%d", &num)) {
				append(instructions, num);
			}

		} else if (matchFlag(current, "-o")) {
			const char *filepath = NEXT_ARG(1);
			FILE *source = fopen(filepath, "w");

			*output = source;

		} else if (matchFlag(current, "-d")) {
			*flags = 1;

		} else if (current == NULL) {
			return ARGPARSE_OK;

		} else {
			parseError(argv[0], "Unknown option '%s'", current);
			return ARGPARSE_ERROR;
		}
	}
}
