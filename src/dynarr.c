#include <stdlib.h>

#include "../defs/dynarr.h"


void append(DynamicArray *arr, int value) {
	if (arr->capacity <= arr->count + 1) {
		arr->capacity = (arr->capacity < 8) ? 8 : 2 * arr->capacity;
		arr->values = realloc(arr->values, sizeof(int) * arr->capacity);
	}

	arr->values[arr->count++] = value;
}
