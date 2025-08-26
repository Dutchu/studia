#include <stdio.h>
#include <malloc.h>

void destroy(int **arr, int how_many);

int main(void) {
    int **arr_2d = malloc(sizeof(int *) * 10);
    if (arr_2d == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    for (int row = 0; row < 10; row++) {
        int *p_row = malloc(sizeof(int) * 10);
        if (p_row == NULL) {
            printf("Failed to allocate memory");
            destroy(arr_2d, row);
            free(arr_2d);
            return 8;
        }
        *(arr_2d + row) = p_row;
    }


    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            *(*(arr_2d + row) + col) = (row+1) * (col+1);
        }
    }

    int curr;
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            curr = *(*(arr_2d + row) + col);
            if (curr < 10) {
                printf("  %d ", curr);
            } else if (curr == 100) {
                printf("%d", curr);
            } else {
                printf(" %d ", curr);
            }
        }
        printf("\n");
    }

    for (int row = 0; row < 10; row++) {
        free(*(arr_2d + row));
    }
    free(arr_2d);
    return 0;
}

void destroy(int **arr, int how_many) {
    for (int i = 0; i < how_many; i++) {
        free(*(arr + i));
    }
}
