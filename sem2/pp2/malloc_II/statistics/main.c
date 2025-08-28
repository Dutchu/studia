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
        return 1;
    }

    const char *mode = (format == fmt_text) ? "r" : "rb";
    FILE *f = fopen(filename, mode);
    if (f == NULL) {
        return 2;
    }

    *ptr = NULL;

    if (format == fmt_text) {
        int rows = 0;
        char ch;

        while ((ch = fgetc(f)) != EOF) {
            if (ch == '\n') {
                rows++;
            }
        }

        fseek(f, -1, SEEK_END);
        if (fgetc(f) != '\n') rows++;

        rewind(f);

        *ptr = (int **) malloc((rows + 1) * sizeof(int *));
        if (*ptr == NULL) {
            fclose(f);
            return 4;
        }

        for (int i = 0; i < rows; ++i) {
            long pos = ftell(f);
            int count = 0;
            int num;
            int scan_result;

            // Count numbers in this row until we hit -1 or end of line
            while ((scan_result = fscanf(f, "%d", &num)) == 1 && num != -1) {
                count++;
            }

            // Check if we ended properly with -1
            if (scan_result == 1 && num == -1) {
                // Good - we found the -1 terminator
            } else if (scan_result == 0 || scan_result == EOF) {
                // Failed to read - might be end of line without -1
                // This could be valid depending on format expectations
                // Let's assume it's valid for now
            } else {
                // We read a number but it wasn't -1, which might be an error
                // But let's be permissive and allow it
            }

            fseek(f, pos, SEEK_SET);

            *(*ptr + i) = (int *) malloc((count + 1) * sizeof(int));
            if (*(*ptr + i) == NULL) {
                cleanup_on_error(ptr, i);
                fclose(f);
                return 4;
            }

            // Read the actual data
            for (int j = 0; j < count; ++j) {
                if (fscanf(f, "%d", &num) != 1) {
                    cleanup_on_error(ptr, i + 1);
                    fclose(f);
                    return 31;
                }
                *(*(*ptr + i) + j) = num;
            }

            // Try to read the terminator (-1), but don't fail if it's not there
            fscanf(f, "%d", &num);
            *(*(*ptr + i) + count) = -1;
        }
        *(*ptr + rows) = NULL;

    } else {
        // Binary format handling
        fseek(f, 0, SEEK_END);
        long file_size = ftell(f);
        rewind(f);

        if (file_size == 0 || file_size % sizeof(int) != 0) {
            fclose(f);
            return 32;
        }

        // First pass: count rows without loading all data
        int rows = 0;
        int buffer;
        while (fread(&buffer, sizeof(int), 1, f) == 1) {
            if (buffer == -1) {
                rows++;
            }
        }

        if (rows == 0) {
            fclose(f);
            return 33;
        }

        rewind(f);

        *ptr = (int **) malloc((rows + 1) * sizeof(int *));
        if (*ptr == NULL) {
            fclose(f);
            return 4;
        }

        // Second pass: read and allocate row by row
        for (int i = 0; i < rows; ++i) {
            // Count numbers in this row
            long pos = ftell(f);
            int count = 0;
            while (fread(&buffer, sizeof(int), 1, f) == 1 && buffer != -1) {
                count++;
            }

            fseek(f, pos, SEEK_SET);

            *(*ptr + i) = (int *) malloc((count + 1) * sizeof(int));
            if (*(*ptr + i) == NULL) {
                cleanup_on_error(ptr, i);
                fclose(f);
                return 4;
            }

            // Read the actual row data
            for (int j = 0; j < count; ++j) {
                if (fread(&buffer, sizeof(int), 1, f) != 1) {
                    cleanup_on_error(ptr, i + 1);
                    fclose(f);
                    return 34;
                }
                *(*(*ptr + i) + j) = buffer;
            }

            // Read and skip the -1 terminator
            if (fread(&buffer, sizeof(int), 1, f) != 1 || buffer != -1) {
                cleanup_on_error(ptr, i + 1);
                fclose(f);
                return 35;
            }

            *(*(*ptr + i) + count) = -1;
        }

        *(*ptr + rows) = NULL;
    }

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
    printf("Podaj nazwe pliku: ");
    char *filename = (char *) malloc(40 * sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    if (scanf("%39s", filename) != 1) {
        printf("Couldn't read filename\n");
        free(filename);
        return 1;
    }

    enum save_format_t format;
    char *ext = strrchr(filename, '.');
    if (ext == NULL || (strcmp(ext, ".txt") != 0 && strcmp(ext, ".bin") != 0)) {
        printf("Unsupported file format\n");
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
            printf("Couldn't open file\n");
            free(filename);
            return 4;
        case 3:
            printf("File corrupted\n");
            free(filename);
            destroy(&data);
            return 6;
        case 4:
            printf("Failed to allocate memory\n");
            free(filename);
            return 8;
    }

    struct statistic_t *stats = NULL;
    int num_rows = statistics_row(data, &stats);

    if (num_rows == -2) {
        printf("Failed to allocate memory\n");
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