#ifndef KIP_DEFS_H
#define KIP_DEFS_H

typedef enum {
	BINOP, IMMOP, HALT,
} FormatSpecifier;

typedef enum {
	ADD, SUB, MUL, LOD,
} Operations;

#endif /* KIP_DEFS_H */
