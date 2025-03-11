#ifndef DYNARR_H
#define DYNARR_H

typedef struct {
	int capacity, count;
	int *values;
} DynamicArray;

void append(DynamicArray *arr, int value);

#endif /* DYNARR_H */
