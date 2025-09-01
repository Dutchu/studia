//
// Created by Bartek on 28.08.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "format_type.h"


struct statistic_t {
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};


int load(const char *filename, int ***ptr, enum save_format_t format);

int statistics_row(int **ptr, struct statistic_t **stats);

void destroy(int ***ptr);

void display(int **ptr);

void cleanup_on_error(int ***ptr, int i);


void display(int **ptr) {
    if (ptr == NULL || *ptr == NULL) {
        return;
    }

    int i = 0;
    while (*(ptr + i) != NULL) {
        int j = 0;
        while (*(*(ptr + i) + j) != -1) {
            printf("%d ", *(*(ptr + i) + j));
            j++;
        }
        printf("\n");
        i++;
    }
}

void cleanup_on_error(int ***ptr, int rows_to_free) {
    if (ptr == NULL || *ptr == NULL) {
        return;
    }

    for (int i = 0; i < rows_to_free; ++i) {
        free(*(*ptr + i));
    }

    free(*ptr);
    *ptr = NULL;
}

int load(const char *filename, int ***ptr, enum save_format_t format) {
    if (filename == NULL || ptr == NULL) {
        return 1; // invalid input
    }

    // validate format flag explicitly
    if (!(format == fmt_text || format == fmt_binary)) {
        return 1; // invalid input
    }

    *ptr = NULL;

    const char *mode = (format == fmt_text) ? "r" : "rb";
    FILE *f = fopen(filename, mode);
    if (f == NULL) {
        return 2; // file open error
    }

    // Pass 1: count rows (every -1 closes one row). Validate structure.
    int rows = 0;
    int inrow_count = 0;
    int val;
    if (format == fmt_text) {
        while (1) {
            int r = fscanf(f, "%d", &val);
            if (r == 1) {
                if (val == -1) { rows++; inrow_count = 0; }
                else { inrow_count++; }
            } else if (r == EOF) {
                if (inrow_count != 0) { fclose(f); return 3; } // unfinished row
                break;
            } else {
                fclose(f); return 3; // invalid token
            }
        }
    } else { // binary
        while (fread(&val, sizeof(int), 1, f) == 1) {
            if (val == -1) { rows++; inrow_count = 0; }
            else { inrow_count++; }
        }
        if (!feof(f)) { fclose(f); return 3; }
        if (inrow_count != 0) { fclose(f); return 3; } // missing final -1
    }

    if (rows == 0) { // no rows found => corrupted
        fclose(f);
        return 3;
    }

    // Allocate top-level pointer array
    int **arr = (int **) malloc(((size_t) rows + 1) * sizeof(int *));
    if (arr == NULL) { fclose(f); return 4; }

    // Pass 2: build rows one by one with minimal extra memory
    rewind(f);
    for (int i = 0; i < rows; ++i) {
        long pos = ftell(f);
        int count = 0;

        // Count items in this row
        if (format == fmt_text) {
            while (1) {
                if (fscanf(f, "%d", &val) != 1) { // malformed
                    for (int k = 0; k < i; ++k) free(*(arr + k));
                    free(arr); fclose(f); return 3;
                }
                if (val == -1) break;
                count++;
            }
        } else {
            while (1) {
                if (fread(&val, sizeof(int), 1, f) != 1) { // malformed
                    for (int k = 0; k < i; ++k) free(*(arr + k));
                    free(arr); fclose(f); return 3;
                }
                if (val == -1) break;
                count++;
            }
        }

        // Allocate exact row size (+1 for -1 terminator we store)
        int *row = (int *) malloc(((size_t) count + 1) * sizeof(int));
        if (row == NULL) {
            for (int k = 0; k < i; ++k) free(*(arr + k));
            free(arr); fclose(f); return 4;
        }

        // Fill row
        if (fseek(f, pos, SEEK_SET) != 0) { // should not fail when using ftell value
            for (int k = 0; k < i; ++k) free(*(arr + k));
            free(row); free(arr); fclose(f); return 3;
        }
        for (int j = 0; j < count; ++j) {
            if (format == fmt_text) {
                if (fscanf(f, "%d", &val) != 1) {
                    for (int k = 0; k < i; ++k) free(*(arr + k));
                    free(row); free(arr); fclose(f); return 3;
                }
            } else {
                if (fread(&val, sizeof(int), 1, f) != 1) {
                    for (int k = 0; k < i; ++k) free(*(arr + k));
                    free(row); free(arr); fclose(f); return 3;
                }
            }
            *(row + j) = val;
        }
        // consume the -1
        if (format == fmt_text) {
            if (fscanf(f, "%d", &val) != 1 || val != -1) {
                for (int k = 0; k < i; ++k) free(*(arr + k));
                free(row); free(arr); fclose(f); return 3;
            }
        } else {
            if (fread(&val, sizeof(int), 1, f) != 1 || val != -1) {
                for (int k = 0; k < i; ++k) free(*(arr + k));
                free(row); free(arr); fclose(f); return 3;
            }
        }

        *(row + count) = -1;
        *(arr + i) = row;
    }

    *(arr + rows) = NULL;
    *ptr = arr;
    fclose(f);
    return 0;
}

void destroy(int ***ptr) {
    if (ptr == NULL || *ptr == NULL) {
        return;
    }

    int i = 0;
    while (*(*ptr + i) != NULL) {
        free(*(*ptr + i));
        i++;
    }
    free(*ptr);
    *ptr = NULL;
}

int statistics_row(int **ptr, struct statistic_t **stats) {
    if (ptr == NULL || stats == NULL) {
        return -1;
    }

    int rows = 0;
    while (*(ptr + rows) != NULL) {
        rows++;
    }

    *stats = (struct statistic_t *) malloc(rows * sizeof(struct statistic_t));
    if (*stats == NULL) {
        return -2;
    }

    for (int i = 0; i < rows; ++i) {
        int *row = *(ptr + i);
        if (*row == -1) {
            (*(stats) + i)->min = -1;
            (*(stats) + i)->max = -1;
            (*(stats) + i)->avg = -1.0f;
            (*(stats) + i)->standard_deviation = -1.0f;
            (*(stats) + i)->range = -1;
            continue;
        }

        int min = *row, max = *row;
        double sum = 0;
        int count = 0;

        while (*(row + count) != -1) {
            int val = *(row + count);
            if (val < min) min = val;
            if (val > max) max = val;
            sum += val;
            count++;
        }

        float avg = sum / count;
        double sum_sq_diff = 0;

        for (int j = 0; j < count; ++j) {
            sum_sq_diff += pow(*(row + j) - avg, 2);
        }

        float std_dev = sqrt(sum_sq_diff / count);

        (*(stats) + i)->min = min;
        (*(stats) + i)->max = max;
        (*(stats) + i)->avg = avg;
        (*(stats) + i)->standard_deviation = std_dev;
        (*(stats) + i)->range = max - min;
    }

    return rows;
}

int main() {
    char *filename = (char *) malloc(40 * sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj nazwe pliku: ");
    if (scanf("%39s", filename) != 1) {
        printf("Couldn't read filename");
        free(filename);
        return 1;
    }

    enum save_format_t format;
    char *ext = strrchr(filename, '.');
    if (ext == NULL || (strcmp(ext, ".txt") != 0 && strcmp(ext, ".bin") != 0)) {
        printf("Unsupported file format");
        free(filename);
        return 7;
    }

    if (strcmp(ext, ".txt") == 0) {
        format = fmt_text;
    } else {
        format = fmt_binary;
    }

    int **data = NULL;
    int err = load(filename, &data, format);

    switch (err) {
        case 2:
            printf("Couldn't open file");
            free(filename);
            return 4;
        case 3:
            printf("File corrupted");
            free(filename);
            destroy(&data);
            return 6;
        case 4:
            printf("Failed to allocate memory");
            free(filename);
            return 8;
    }

    struct statistic_t *stats = NULL;
    int num_rows = statistics_row(data, &stats);

    if (num_rows == -2) {
        printf("Failed to allocate memory");
        free(filename);
        destroy(&data);
        return 8;
    }

    for (int i = 0; i < num_rows; ++i) {
        printf("%d %d %d %.2f %.2f\n",
               (*(stats + i)).min,
               (*(stats + i)).max,
               (*(stats + i)).range,
               (*(stats + i)).avg,
               (*(stats + i)).standard_deviation);
    }

    free(filename);
    free(stats);
    destroy(&data);

    return 0;
}
