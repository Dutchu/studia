#include <stdio.h>
#include <stdlib.h>

int create_array_2d_2(int ***ptr, int width, int height);

void destroy_array_2d(int ***ptr, int height);

void display_array_2d(int **ptr, int width, int height);

int sum_array_2d(int **ptr, int width, int height);

int sum_row(int *ptr, int width);

int read_row_from_user(int *row_ptr, int width);


int main(void) {
    int width, height;
    int **my_array = NULL;

    printf("Podaj szerokość i wysokość: ");
    if (scanf("%d %d", &width, &height) != 2) {
        printf("incorrect input\n");
        return 1;
    }

    int create_status = create_array_2d_2(&my_array, width, height);
    if (create_status == 1) {
        printf("incorrect input data\n");
        return 2;
    }
    if (create_status == 2) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj liczby:\n");
    for (int i = 0; i < height; ++i) {
        if (read_row_from_user(*(my_array + i), width) != 0) {
            printf("incorrect input\n");
            destroy_array_2d(&my_array, height);
            return 1;
        }
    }

    display_array_2d(my_array, width, height);


    for (int i = 0; i < height; ++i) {
        printf("%d\n", sum_row(*(my_array + i), width));
    }


    printf("%d\n", sum_array_2d(my_array, width, height));


    destroy_array_2d(&my_array, height);

    return 0;
}

int create_array_2d_2(int ***ptr, int width, int height) {
    if (ptr == NULL || width < 1 || height < 1) {
        return 1;
    }

    int **array = (int **) malloc(height * sizeof(int *));
    if (array == NULL) {
        return 2;
    }

    for (int i = 0; i < height; ++i) {
        *(array + i) = (int *) malloc(width * sizeof(int));
        if (*(array + i) == NULL) {

            for (int j = 0; j < i; ++j) {
                free(*(array + j));
            }
            free(array);
            return 2;
        }
    }

    *ptr = array;
    return 0;
}

void destroy_array_2d(int ***ptr, int height) {
    if (ptr == NULL || *ptr == NULL) {
        return;
    }

    for (int i = 0; i < height; ++i) {
        free(*(*ptr + i));
    }
    free(*ptr);
    *ptr = NULL;
}

void display_array_2d(int **ptr, int width, int height) {
    if (ptr == NULL || width < 1 || height < 1) {
        return;
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%d ", *(*(ptr + i) + j));
        }
        printf("\n");
    }
}

int sum_row(int *ptr, int width) {
    if (ptr == NULL || width < 1) {
        return -1;
    }
    int sum = 0;
    for (int i = 0; i < width; ++i) {
        sum += *(ptr + i);
    }
    return sum;
}

int sum_array_2d(int **ptr, int width, int height) {
    if (ptr == NULL || width < 1 || height < 1) {
        return -1;
    }
    int total_sum = 0;
    for (int i = 0; i < height; ++i) {
        total_sum += sum_row(*(ptr + i), width);
    }
    return total_sum;
}

int read_row_from_user(int *row_ptr, int width) {
    for (int i = 0; i < width; ++i) {
        if (scanf("%d", row_ptr + i) != 1) {
            return 1;
        }
    }
    return 0;
}