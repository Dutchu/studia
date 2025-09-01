#pragma once

// Define both the enum tag and a typedef alias so that
// both `enum data_type_t` and `data_type_t` are valid.
typedef enum data_type_t {
    data_type_short = 0,
    data_type_int = 1,
    data_type_float = 2,
    data_type_double = 3,
    data_type_long = 4
} data_type_t;
