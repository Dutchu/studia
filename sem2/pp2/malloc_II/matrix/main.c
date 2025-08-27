#include <stdio.h>
#include <stdlib.h>


struct matrix_t {
    int **ptr;
    int width;
    int height;
};


int matrix_create(struct matrix_t *m, int width, int height);
int matrix_read(struct matrix_t *m);
void matrix_display(const struct matrix_t *m);
void matrix_destroy(struct matrix_t *m);


int main(void) {
    struct matrix_t matrix;
    int width, height;

    printf("Podaj szerokość i wysokość: ");
    if (scanf("%d %d", &width, &height) != 2) {
        printf("incorrect input\n");
        return 1;
    }

    
    int create_status = matrix_create(&matrix, width, height);
    if (create_status == 1) {
        printf("incorrect input data\n");
        return 2;
    }
    if (create_status == 2) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    
    printf("Podaj wartości: \n");
    int read_status = matrix_read(&matrix);
    if (read_status != 0) {
        printf("incorrect input\n");
        matrix_destroy(&matrix);
        return 1;
    }

    
    matrix_display(&matrix);
    matrix_destroy(&matrix);

    return 0;
}

int matrix_create(struct matrix_t *m, int width, int height) {
    if (m == NULL || width < 1 || height < 1) {
        return 1; 
    }

    m->width = width;
    m->height = height;
    m->ptr = (int **)malloc(height * sizeof(int *));

    if (m->ptr == NULL) {
        return 2; 
    }

    
    for (int i = 0; i < height; ++i) {
        *(m->ptr + i) = (int *)malloc(width * sizeof(int));

        
        if (*(m->ptr + i) == NULL) {
            
            m->height = i;
            
            matrix_destroy(m);
            return 2; 
        }
    }

    return 0; 
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

void matrix_display(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) {
        return; 
    }

    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            printf("%d ", *(*(m->ptr + i) + j));
        }
        printf("\n");
    }
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