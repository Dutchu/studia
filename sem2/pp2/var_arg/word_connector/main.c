// Solution for "word_connector" task
// Requirements summary (from desc.txt):
// - Implement int* count_words(const char *filename, int *err_code, int N, ...)
// - Return an array of counts for provided N words read from file
// - Error codes: 0 success, 1 invalid args, 2 file open error, 3 alloc error
// - Provide a program that prints each count on its own line
// - Program exit codes: 0 success, 4 couldn't open file, 8 alloc failed, 9 not enough args
// - Do not use the [] operator anywhere in the program code

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

static int* count_words_core(const char *filename, int *err_code, int N, const char **words);

static int is_alpha_char_int(int c) {
    return isalpha((unsigned char)c) ? 1 : 0;
}

int* count_words(const char *filename, int *err_code, int N, ...) {
    if (!filename || N <= 0) {
        if (err_code) *err_code = 1;
        return NULL;
    }

    va_list ap;
    va_start(ap, N);

    // Process words one by one without storing them
    FILE *f = fopen(filename, "r");
    if (!f) {
        if (err_code) *err_code = 2;
        va_end(ap);
        return NULL;
    }

    int *counts = (int*)malloc((size_t)N * sizeof(int));
    if (!counts) {
        if (err_code) *err_code = 3;
        fclose(f);
        va_end(ap);
        return NULL;
    }
    int *cp = counts;
    int i;
    for (i = 0; i < N; ++i) {
        *(cp + i) = 0;
    }

    for (i = 0; i < N; ++i) {
        const char *word = va_arg(ap, const char*);
        if (!word) {
            if (err_code) *err_code = 1;
            free((void*)counts);
            fclose(f);
            va_end(ap);
            return NULL;
        }

        // Count occurrences of this single word by scanning the file
        rewind(f);
        int in_token = 0;
        int c_int;
        const char *p = word;
        int match = 1; // still equal to word so far
        while ((c_int = fgetc(f)) != EOF) {
            if (is_alpha_char_int(c_int)) {
                if (!in_token) {
                    in_token = 1;
                    p = word;
                    match = 1;
                }
                if (match) {
                    if (*p == '\0') {
                        match = 0;
                    } else if (*p == (char)c_int) {
                        ++p;
                    } else {
                        match = 0;
                    }
                }
            } else {
                if (in_token) {
                    if (match && *p == '\0') {
                        int v = *(cp + i);
                        *(cp + i) = v + 1;
                    }
                    in_token = 0;
                }
            }
        }
        if (in_token) {
            if (match && *p == '\0') {
                int v = *(cp + i);
                *(cp + i) = v + 1;
            }
        }
    }
    va_end(ap);

    fclose(f);
    if (err_code) *err_code = 0;
    return counts;
}

// Keep a core version that accepts an array to support main()
static int* count_words_core(const char *filename, int *err_code, int N, const char **words) {
    if (!filename || N <= 0) {
        if (err_code) *err_code = 1;
        return NULL;
    }
    FILE *f = fopen(filename, "r");
    if (!f) {
        if (err_code) *err_code = 2;
        return NULL;
    }
    int *counts = (int*)malloc((size_t)N * sizeof(int));
    if (!counts) {
        if (err_code) *err_code = 3;
        fclose(f);
        return NULL;
    }
    int *cp = counts;
    int i;
    for (i = 0; i < N; ++i) {
        *(cp + i) = 0;
    }

    for (i = 0; i < N; ++i) {
        const char *word = *(words + i);
        if (!word) {
            if (err_code) *err_code = 1;
            free((void*)counts);
            fclose(f);
            return NULL;
        }
        rewind(f);
        int in_token = 0;
        int c_int;
        const char *p = word;
        int match = 1;
        while ((c_int = fgetc(f)) != EOF) {
            if (is_alpha_char_int(c_int)) {
                if (!in_token) {
                    in_token = 1;
                    p = word;
                    match = 1;
                }
                if (match) {
                    if (*p == '\0') {
                        match = 0;
                    } else if (*p == (char)c_int) {
                        ++p;
                    } else {
                        match = 0;
                    }
                }
            } else {
                if (in_token) {
                    if (match && *p == '\0') {
                        int v = *(cp + i);
                        *(cp + i) = v + 1;
                    }
                    in_token = 0;
                }
            }
        }
        if (in_token) {
            if (match && *p == '\0') {
                int v = *(cp + i);
                *(cp + i) = v + 1;
            }
        }
    }
    fclose(f);
    if (err_code) *err_code = 0;
    return counts;
}

int main(int argc, char **argv) {
    // Require at least: program file word
    if (argc < 3) {
        const char *msg = "Not enough arguments\n";
        const char *p = msg;
        while (*p) { fputc(*p, stdout); ++p; }
        return 9;
    }

    // Parse filename and words via pointer arithmetic (no [])
    char **argp = argv;
    // skip program name
    ++argp;
    const char *filename = *argp;
    ++argp;
    int N = argc - 2;

    // Build array of pointers to words (reuse argp as-is)
    const char **words = (const char**)argp;

    // Use helper that accepts array; the varargs function is provided as required
    int err = 0;
    int *counts = count_words_core(filename, &err, N, words);
    if (!counts) {
        if (err == 2) {
            const char *msg = "Couldn't open file\n";
            const char *p = msg;
            while (*p) { fputc(*p, stdout); ++p; }
            return 4;
        } else if (err == 3) {
            const char *msg = "Failed to allocate memory\n";
            const char *p = msg;
            while (*p) { fputc(*p, stdout); ++p; }
            return 8;
        } else {
            // Invalid input should not happen here; treat as not enough args
            const char *msg = "Not enough arguments\n";
            const char *p = msg;
            while (*p) { fputc(*p, stdout); ++p; }
            return 9;
        }
    }

    // Print counts line by line
    int i;
    for (i = 0; i < N; ++i) {
        // print integer without using []
        fprintf(stdout, "%d\n", *(counts + i));
    }

    free((void*)counts);
    return 0;
}
