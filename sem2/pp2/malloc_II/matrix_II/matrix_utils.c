#include "matrix_utils.h"
#include <stdio.h>
#include <stdlib.h>

int matrix_create(struct matrix_t *m, int width, int height) {
    if (m == NULL || width < 1 || height < 1) {
        return 1;
    }

    m->width = width;
    m->height = height;
    m->ptr = (int**)malloc((size_t)height * sizeof(int*));
    if (m->ptr == NULL) {
        m->width = 0;
        m->height = 0;
        return 2;
    }

    for (int i = 0; i < height; ++i) {
        *(m->ptr + i) = (int*)malloc((size_t)width * sizeof(int));
        if (*(m->ptr + i) == NULL) {
            for (int j = 0; j < i; ++j) {
                free(*(m->ptr + j));
            }
            free(m->ptr);
            m->ptr = NULL;
            m->width = 0;
            m->height = 0;
            return 2;
        }
    }
    return 0;
}

void matrix_destroy(struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL) {
        return;
    }
    for (int i = 0; i < m->height; ++i) {
        free(*(m->ptr + i));
    }
    free(m->ptr);
    m->ptr = NULL;
    m->width = 0;
    m->height = 0;
}

int matrix_display(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) {
        return 1;
    }
    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            if (printf("%d ", *(*(m->ptr + i) + j)) < 0) {
                return 2;
            }
        }
        if (printf("\n") < 0) {
            return 2;
        }
    }
    return 0;
}

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
    if (m == NULL || m->ptr == NULL || filename == NULL || m->width < 1 || m->height < 1) {
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
        if (*((m->ptr) + i) == NULL) { fclose(f); return 1; }
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
    if (m == NULL || m->ptr == NULL || filename == NULL || m->width < 1 || m->height < 1) {
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
        if (*((m->ptr) + i) == NULL) { fclose(f); return 1; }
        if (fwrite(*(m->ptr + i), sizeof(int), m->width, f) != (size_t) m->width) {
            fclose(f);
            return 3;
        }
    }
    fclose(f);
    return 0;
}

int matrix_save_transposed_t(const struct matrix_t *m, const char *filename) {
    if (m == NULL || m->ptr == NULL || filename == NULL || m->width < 1 || m->height < 1) {
        return 1;
    }

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        return 2;
    }

    /* swapped dimensions: width' = height, height' = width */
    if (fprintf(f, "%d %d\n", m->height, m->width) < 0) {
        fclose(f);
        return 3;
    }

    for (int i = 0; i < m->width; ++i) {
        for (int j = 0; j < m->height; ++j) {
            int val = *(*(m->ptr + j) + i);
            if (fprintf(f, "%d ", val) < 0) {
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

int matrix_save_transposed_b(const struct matrix_t *m, const char *filename) {
    if (m == NULL || m->ptr == NULL || filename == NULL || m->width < 1 || m->height < 1) {
        return 1;
    }

    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        return 2;
    }

    /* swapped dimensions: width' = height, height' = width */
    int w_prime = m->height;
    int h_prime = m->width;
    if (fwrite(&w_prime, sizeof(int), 1, f) != 1) {
        fclose(f);
        return 3;
    }
    if (fwrite(&h_prime, sizeof(int), 1, f) != 1) {
        fclose(f);
        return 3;
    }

    for (int i = 0; i < h_prime; ++i) {
        for (int j = 0; j < w_prime; ++j) {
            int val = *(*((m->ptr) + j) + i);
            if (fwrite(&val, sizeof(int), 1, f) != 1) {
                fclose(f);
                return 3;
            }
        }
    }

    fclose(f);
    return 0;
}
