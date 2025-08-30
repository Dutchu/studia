// Macros to generate array structs and API for a given TYPE
// Generates:
// - struct array_TYPE_t { int size; int capacity; TYPE *data; };
// - struct array_TYPE_t *create_array_TYPE(int size);
// - void free_array_TYPE(struct array_TYPE_t *array);
// - int save_array_TYPE(const struct array_TYPE_t *array, const char *filename);
// - int load_array_TYPE(struct array_TYPE_t **array, const char *filename);
// - int sort_array_TYPE(struct array_TYPE_t *array);

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

// Define the array structure type for TYPE
#define DEFINE_ARRAY(TYPE) \
    struct array_##TYPE##_t { \
        int size; \
        int capacity; \
        TYPE *data; \
    };

// Create function for TYPE
#define CREATE_ARRAY(TYPE) \
    struct array_##TYPE##_t *create_array_##TYPE(int size) { \
        if (size <= 0) { \
            return NULL; \
        } \
        struct array_##TYPE##_t *arr = (struct array_##TYPE##_t *)malloc(sizeof(struct array_##TYPE##_t)); \
        if (!arr) { \
            return NULL; \
        } \
        arr->size = 0; \
        arr->capacity = size; \
        arr->data = (TYPE *)malloc((size_t)size * sizeof(TYPE)); \
        if (!arr->data) { \
            free(arr); \
            return NULL; \
        } \
        return arr; \
    }

// Free function for TYPE
#define FREE_ARRAY(TYPE) \
    void free_array_##TYPE(struct array_##TYPE##_t *array) { \
        if (!array) { \
            return; \
        } \
        free(array->data); \
        free(array); \
    }

// Save function for TYPE
#define SAVE_ARRAY(TYPE) \
    int save_array_##TYPE(const struct array_##TYPE##_t *array, const char *filename) { \
        if (!array || !filename) { \
            return 1; \
        } \
        if (array->size < 0) { \
            return 1; \
        } \
        if (array->capacity < 0) { \
            return 1; \
        } \
        if (array->size > array->capacity) { \
            return 1; \
        } \
        if (array->size == 0 && array->data != NULL) { \
            return 1; \
        } \
        if (array->size > 0 && !array->data) { \
            return 1; \
        } \
        FILE *f = fopen(filename, "wb"); \
        if (!f) { \
            return 2; \
        } \
        int count = array->size; \
        size_t written = fwrite(&count, sizeof(int), 1, f); \
        if (written != 1) { \
            fclose(f); \
            return 2; \
        } \
        if (count > 0) { \
            written = fwrite(array->data, sizeof(TYPE), (size_t)count, f); \
            if (written != (size_t)count) { \
                fclose(f); \
                return 2; \
            } \
        } \
        fclose(f); \
        return 0; \
    }

// Load function for TYPE
#define LOAD_ARRAY(TYPE) \
    int load_array_##TYPE(struct array_##TYPE##_t **array, const char *filename) { \
        if (!array || !filename) { \
            return 1; \
        } \
        *array = NULL; \
        FILE *f = fopen(filename, "rb"); \
        if (!f) { \
            return 2; \
        } \
        int count = 0; \
        size_t readc = fread(&count, sizeof(int), 1, f); \
        if (readc != 1) { \
            fclose(f); \
            return 3; \
        } \
        if (count < 0) { \
            fclose(f); \
            return 3; \
        } \
        struct array_##TYPE##_t *arr = (struct array_##TYPE##_t *)malloc(sizeof(struct array_##TYPE##_t)); \
        if (!arr) { \
            fclose(f); \
            return 4; \
        } \
        arr->size = count; \
        arr->capacity = count; \
        if (count == 0) { \
            arr->data = NULL; \
        } else { \
            arr->data = (TYPE *)malloc((size_t)count * sizeof(TYPE)); \
            if (!arr->data) { \
                free(arr); \
                fclose(f); \
                return 4; \
            } \
            size_t need = (size_t)count; \
            size_t got = fread(arr->data, sizeof(TYPE), need, f); \
            if (got != need) { \
                free(arr->data); \
                free(arr); \
                fclose(f); \
                return 3; \
            } \
        } \
        /* verify no extra data present */ \
        int extr = fgetc(f); \
        if (extr != EOF) { \
            if (arr->data) free(arr->data); \
            free(arr); \
            fclose(f); \
            return 3; \
        } else if (ferror(f)) { \
            if (arr->data) free(arr->data); \
            free(arr); \
            fclose(f); \
            return 3; \
        } \
        fclose(f); \
        *array = arr; \
        return 0; \
    }

// Sort function for TYPE (ascending)
#define SORT_ARRAY(TYPE) \
    static int compare_##TYPE(const void *a, const void *b) { \
        const TYPE *pa = (const TYPE *)a; \
        const TYPE *pb = (const TYPE *)b; \
        if (*pa < *pb) return -1; \
        if (*pa > *pb) return 1; \
        return 0; \
    } \
    int sort_array_##TYPE(struct array_##TYPE##_t *array) { \
        if (!array) { \
            return 1; \
        } \
        if (array->size < 0) { \
            return 1; \
        } \
        if (array->capacity < 0) { \
            return 1; \
        } \
        if (array->size > array->capacity) { \
            return 1; \
        } \
        if (array->size == 0 && array->data != NULL) { \
            return 1; \
        } \
        if (array->size > 0 && !array->data) { \
            return 1; \
        } \
        if (array->size <= 1) { \
            return 0; \
        } \
        qsort(array->data, (size_t)array->size, sizeof(TYPE), compare_##TYPE); \
        return 0; \
    }

#endif // FUNCTIONS_H
