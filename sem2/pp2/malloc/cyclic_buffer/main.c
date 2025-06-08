//
// Created by Bartek on 07.06.2025.
//

#include <stdlib.h>
#include <stdio.h>
#include "circular_buffer.h"

int main() {

    struct circular_buffer_t *ptr_cb = NULL;

    circular_buffer_create_struct(&ptr_cb, 10);

    for (int i = 0; i < 30; i++) {
        circular_buffer_push_back(ptr_cb, i);
        printf("%d: ", i);
        circular_buffer_display(ptr_cb);
    }

    circular_buffer_destroy_struct(&ptr_cb);

    return 0;
}