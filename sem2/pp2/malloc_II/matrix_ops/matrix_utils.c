#include "matrix_utils.h"
#include <stdio.h>
#include <stdlib.h>

struct matrix_t* matrix_create_struct(int width, int height) {
    if (width < 1 || height < 1) {
        return NULL;
    }

    struct matrix_t* m = (struct matrix_t*)malloc(sizeof(struct matrix_t));
    if (m == NULL) {
        return NULL;
    }

    m->width = width;
    m->height = height;
    m->ptr = (int **)malloc(height * sizeof(int *));

    if (m->ptr == NULL) {
        free(m); 
        return NULL;
    }
    
    for (int i = 0; i < height; ++i) {
        *(m->ptr + i) = (int *)malloc(width * sizeof(int));
        if (*(m->ptr + i) == NULL) {
            
            for (int j = 0; j < i; ++j) {
                free(*(m->ptr + j));
            }
            free(m->ptr);
            free(m);
            return NULL;
        }
    }
    return m;
}

void matrix_destroy_struct(struct matrix_t **m) {
    if (m == NULL || *m == NULL) {
        return;
    }

    if ((**m).ptr != NULL) {
        for (int i = 0; i < (**m).height; ++i) {
            free(*((**m).ptr + i));
        }
        free((**m).ptr);
    }

    free(*m);
    *m = NULL;
}

int matrix_read(struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) {
        return 1;
    }
    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            if (scanf("%d", (*(m->ptr + i) + j)) != 1) {
                return 2;
            }
        }
    }
    return 0;
}

struct matrix_t* matrix_transpose(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL) {
        return NULL;
    }

    struct matrix_t* transposed_m = matrix_create_struct(m->height, m->width);
    if (transposed_m == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            *(*(transposed_m->ptr + j) + i) = *(*(m->ptr + i) + j);
        }
    }
    return transposed_m;
}


int matrix_save_t(const struct matrix_t *m, const char *filename) {
    if (m == NULL || m->ptr == NULL || filename == NULL) {
        return 1;
    }

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        return 2;
    }

    if (fprintf(f, "%d %d\n", m->width, m->height) < 0) {
        fclose(f);
        return 3;
    }

    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            if (fprintf(f, "%d ", *(*(m->ptr + i) + j)) < 0) {
                fclose(f);
                return 3;
            }
        }
        if (fprintf(f, "\n") < 0) {
            fclose(f);
            return 3;
        }
    }
    fclose(f);
    return 0;
}

int matrix_save_b(const struct matrix_t *m, const char *filename) {
    if (m == NULL || m->ptr == NULL || filename == NULL) {
        return 1;
    }

    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        return 2;
    }

    if (fwrite(&(m->width), sizeof(int), 1, f) != 1) {
        fclose(f);
        return 3;
    }
    if (fwrite(&(m->height), sizeof(int), 1, f) != 1) {
        fclose(f);
        return 3;
    }

    for (int i = 0; i < m->height; ++i) {
        if (fwrite(*(m->ptr + i), sizeof(int), m->width, f) != (size_t) m->width) {
            fclose(f);
            return 3;
        }
    }
    fclose(f);
    return 0;
}

struct matrix_t* matrix_copy(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL) {
        return NULL;
    }
    struct matrix_t* new_m = matrix_create_struct(m->width, m->height);
    if (new_m == NULL) {
        return NULL;
    }
    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            *(*(new_m->ptr + i) + j) = *(*(m->ptr + i) + j);
        }
    }
    return new_m;
}

struct matrix_t* matrix_add(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (m1 == NULL || m2 == NULL || m1->ptr == NULL || m2->ptr == NULL ||
        m1->width != m2->width || m1->height != m2->height) {
        return NULL;
    }
    struct matrix_t* result = matrix_create_struct(m1->width, m1->height);
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < m1->height; ++i) {
        for (int j = 0; j < m1->width; ++j) {
            *(*(result->ptr + i) + j) = *(*(m1->ptr + i) + j) + *(*(m2->ptr + i) + j);
        }
    }
    return result;
}

struct matrix_t* matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (m1 == NULL || m2 == NULL || m1->ptr == NULL || m2->ptr == NULL ||
        m1->width != m2->width || m1->height != m2->height) {
        return NULL;
    }
    struct matrix_t* result = matrix_create_struct(m1->width, m1->height);
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < m1->height; ++i) {
        for (int j = 0; j < m1->width; ++j) {
            *(*(result->ptr + i) + j) = *(*(m1->ptr + i) + j) - *(*(m2->ptr + i) + j);
        }
    }
    return result;
}

struct matrix_t* matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (m1 == NULL || m2 == NULL || m1->ptr == NULL || m2->ptr == NULL ||
        m1->width != m2->height) {
        return NULL;
    }
    struct matrix_t* result = matrix_create_struct(m2->width, m1->height);
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < result->height; ++i) {
        for (int j = 0; j < result->width; ++j) {
            int sum = 0;
            for (int k = 0; k < m1->width; ++k) {
                sum += *(*(m1->ptr + i) + k) * *(*(m2->ptr + k) + j);
            }
            *(*(result->ptr + i) + j) = sum;
        }
    }
    return result;
}

struct matrix_t* matrix_load_t(const char *filename, int *err_code) {
    if (filename == NULL) {
        if (err_code) *err_code = 1;
        return NULL;
    }
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        if (err_code) *err_code = 2;
        return NULL;
    }
    int width, height;
    if (fscanf(f, "%d %d", &width, &height) != 2) {
        if (err_code) *err_code = 3;
        fclose(f);
        return NULL;
    }
    struct matrix_t* m = matrix_create_struct(width, height);
    if (m == NULL) {
        if (err_code) *err_code = 4;
        fclose(f);
        return NULL;
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (fscanf(f, "%d", (*(m->ptr + i) + j)) != 1) {
                if (err_code) *err_code = 3;
                matrix_destroy_struct(&m);
                fclose(f);
                return NULL;
            }
        }
    }
    if (err_code) *err_code = 0;
    fclose(f);
    return m;
}

struct matrix_t* matrix_load_b(const char *filename, int *err_code) {
    if (filename == NULL) {
        if (err_code) *err_code = 1;
        return NULL;
    }
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        if (err_code) *err_code = 2;
        return NULL;
    }
    int width, height;
    if (fread(&width, sizeof(int), 1, f) != 1 || fread(&height, sizeof(int), 1, f) != 1) {
        if (err_code) *err_code = 3;
        fclose(f);
        return NULL;
    }
    struct matrix_t* m = matrix_create_struct(width, height);
    if (m == NULL) {
        if (err_code) *err_code = 4;
        fclose(f);
        return NULL;
    }
    for (int i = 0; i < height; ++i) {
        if (fread(*(m->ptr + i), sizeof(int), width, f) != (size_t)width) {
            if (err_code) *err_code = 3;
            matrix_destroy_struct(&m);
            fclose(f);
            return NULL;
        }
    }
    if (err_code) *err_code = 0;
    fclose(f);
    return m;
}

void matrix_display(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) {
        printf("Error\n");
        return;
    }
    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            printf("%d ", *(*(m->ptr + i) + j));
        }
        printf("\n");
    }
}
