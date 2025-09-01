#pragma once

#include <stdarg.h>
#include "data_type.h"

// Variadic function that concatenates N arrays (of the same data type)
// Each input array must be terminated by a sentinel value of -1 (or -1.0 for floating types).
// Returns a newly allocated array containing the concatenation (without sentinels), or NULL on error.
void *connect(enum data_type_t type, int arrays_count, ...);
