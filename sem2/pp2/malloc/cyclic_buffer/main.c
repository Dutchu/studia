//
// Created by Bartek on 07.06.2025.
//

#include <stdlib.h>
#include <stdio.h>
#include "circular_buffer.h"

int main() {

    struct circular_buffer_t *ptr_cb = NULL;
    int err;

    circular_buffer_create_struct(&ptr_cb, 10);

    for (int i = 0; i < 30; i++) {
        circular_buffer_push_back(ptr_cb, i);
        printf("%d: ", i);
        circular_buffer_display(ptr_cb);
    }

    for (int i = 0; i < 30; i++) {

        if (i < 15) {
            circular_buffer_pop_front(ptr_cb, &err);
            if (err != 0) {
                printf("[%d] %d: ",err, i);
            } else {
                printf("%d: ", i);
            }
            circular_buffer_display(ptr_cb);
        } else if (i < 25) {
            circular_buffer_push_back(ptr_cb, i);
            printf("%d: ", i);
            circular_buffer_display(ptr_cb);
        } else {
            circular_buffer_pop_front(ptr_cb, &err);
            if (err != 0) {
                printf("[%d] %d: ",err, i);
            } else {
                printf("%d: ", i);
            }
            circular_buffer_display(ptr_cb);
        }

    }

    circular_buffer_destroy_struct(&ptr_cb);

    return 0;
}