#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static size_t cstrlen(const char *s) {
    if (!s) return 0;
    const char *p = s;
    while (*p) ++p;
    return (size_t)(p - s);
}


static int is_upper_word(const char *s) {
    if (!s || *s == '\0') return 0;
    const char *p = s;
    while (*p) {
        if (*p < 'A' || *p > 'Z') return 0;
        ++p;
    }
    return 1;
}


static int first_common_for_horizontal(const char *vertical, const char *horizontal, int *i_out, int *j_out) {
    if (!vertical || !horizontal) return 0;
    const char *hp = horizontal;
    for (; *hp; ++hp) {
        const char c = *hp;
        const char *vp = vertical;
        for (; *vp; ++vp) {
            if (*vp == c) {
                if (i_out) *i_out = (int)(vp - vertical);
                if (j_out) *j_out = (int)(hp - horizontal);
                return 1;
            }
        }
    }
    return 0;
}


static void free_rows(char **rows) {
    if (rows) {
        free(rows);
    }
}


static int rows_count(char **rows) {
    if (!rows) return 0;
    int n = 0;
    char **p = rows;
    while (*p) {
        ++n;
        ++p;
    }
    return n;
}


static size_t max_row_len(char **rows) {
    size_t m = 0;
    if (!rows) return 0;
    char **p = rows;
    while (*p) {
        size_t L = cstrlen(*p);
        if (L > m) m = L;
        ++p;
    }
    return m;
}


int create_leading_word_cross(const char *first, const char *second, char ***result);
int create_double_leading_word_cross(
        const char *first, const char *second, const char *third, const char *fourth,
        char ***result, char ***first_cross, char ***second_cross);
void destroy(char **words);


int create_leading_word_cross(const char *first, const char *second, char ***result) {
    if (!result) return -1;
    *result = NULL;

    if (!first || !second || !is_upper_word(first) || !is_upper_word(second))
        return -1;

    int i = -1, j = -1;
    if (!first_common_for_horizontal(first, second, &i, &j))
        return -2;

    const size_t lenV = cstrlen(first);
    const size_t lenH = cstrlen(second);
    const int height = (int)lenV;

    
    size_t char_data_size = 0;
    int r;
    for (r = 0; r < height; ++r) {
        if (r == i) {
            
            char_data_size += lenH + 1; 
        } else {
            
            char_data_size += (size_t)j + 1 + 1; 
        }
    }

    
    size_t ptr_array_size = ((size_t)height + 1) * sizeof(char*);

    
    char *block = (char*)malloc(ptr_array_size + char_data_size);
    if (!block) return -3;

    char **rows = (char**)block;
    char *char_buffer = block + ptr_array_size;

    
    for (r = 0; r < height; ++r) {
        *(rows + r) = char_buffer;

        if (r == i) {
            size_t row_len = lenH;
            memcpy(char_buffer, second, row_len);
            *(char_buffer + row_len) = '\0';
            char_buffer += row_len + 1;
        } else {
            size_t row_len = (size_t)j + 1;
            memset(char_buffer, ' ', j);
            *(char_buffer + j) = *(first + r);
            *(char_buffer + row_len) = '\0';
            char_buffer += row_len + 1;
        }
    }

    *(rows + height) = NULL; 
    *result = rows;
    return i;
}


int create_double_leading_word_cross(
        const char *first, const char *second, const char *third, const char *fourth,
        char ***result, char ***first_cross, char ***second_cross) {

    // All output pointers must be provided
    if (!result || !first_cross || !second_cross) {
        return 1;
    }

    *result = NULL;
    *first_cross = NULL;
    *second_cross = NULL;

    if (!first || !second || !third || !fourth ||
        !is_upper_word(first) || !is_upper_word(second) ||
        !is_upper_word(third) || !is_upper_word(fourth)) {
        return 1;
    }

    char **crossL = NULL, **crossR = NULL;
    
    
    int rowL = create_leading_word_cross(second, first, &crossL);
    if (rowL < 0) {
        if (rowL == -2) return 2;
        if (rowL == -3) return 3;
        return 1;
    }

    
    int rowR = create_leading_word_cross(fourth, third, &crossR);
    if (rowR < 0) {
        free_rows(crossL);
        if (rowR == -2) return 2;
        if (rowR == -3) return 3;
        return 1;
    }

    const int hL = rows_count(crossL);
    const int hR = rows_count(crossR);
    const size_t wL = max_row_len(crossL);
    const int gap = 3;

    const int maxAbove = (rowL > rowR ? rowL : rowR);
    const int belowL = hL - rowL - 1;
    const int belowR = hR - rowR - 1;
    const int maxBelow = (belowL > belowR ? belowL : belowR);
    const int H = maxAbove + 1 + maxBelow;

    
    size_t ptr_array_size = ((size_t)H + 1) * sizeof(char*);
    size_t char_data_size = 0;
    int r;
    for (r = 0; r < H; ++r) {
        const int idxL = r - (maxAbove - rowL);
        const int idxR = r - (maxAbove - rowR);
        size_t left_len = 0, right_len = 0;
        if (idxL >= 0 && idxL < hL) {
            const char* rowLeft = *(crossL + idxL);
            left_len = cstrlen(rowLeft);
        }
        if (idxR >= 0 && idxR < hR) {
            const char* rowRight = *(crossR + idxR);
            right_len = cstrlen(rowRight);
        }
        size_t row_total = left_len;
        if (right_len > 0) {
            
            row_total += (wL - left_len) + gap + right_len;
        }
        char_data_size += row_total + 1; 
    }

    char *block = (char*)malloc(ptr_array_size + char_data_size);
    if (!block) {
        free_rows(crossL);
        free_rows(crossR);
        return 3;
    }

    char **out = (char**)block;
    char *char_buffer = block + ptr_array_size;

    
    for (r = 0; r < H; ++r) {
        *(out + r) = char_buffer;

        const int idxL = r - (maxAbove - rowL);
        const int idxR = r - (maxAbove - rowR);
        size_t left_len = 0, right_len = 0;
        const char *rowLeft = NULL, *rowRight = NULL;
        if (idxL >= 0 && idxL < hL) {
            rowLeft = *(crossL + idxL);
            left_len = cstrlen(rowLeft);
        }
        if (idxR >= 0 && idxR < hR) {
            rowRight = *(crossR + idxR);
            right_len = cstrlen(rowRight);
        }

        
        if (left_len > 0) {
            memcpy(char_buffer, rowLeft, left_len);
        }
        char_buffer += left_len;

        if (right_len > 0) {
            
            size_t pad = wL - left_len;
            if (pad > 0) {
                memset(char_buffer, ' ', pad);
                char_buffer += pad;
            }
            
            memset(char_buffer, ' ', gap);
            char_buffer += gap;
            
            memcpy(char_buffer, rowRight, right_len);
            char_buffer += right_len;
        }

        
        *char_buffer = '\0';
        ++char_buffer;
    }
    *(out + H) = NULL;

    if (first_cross) *first_cross = crossL; else free_rows(crossL);
    if (second_cross) *second_cross = crossR; else free_rows(crossR);
    if (result) *result = out; else free_rows(out);

    return 0;
}


void destroy(char **words) {
    free_rows(words);
}

#ifndef NO_MAIN
int main(void) {
    char *w1 = (char*)malloc(11);
    char *w2 = (char*)malloc(11);
    char *w3 = (char*)malloc(11);
    char *w4 = (char*)malloc(11);

    if (!w1 || !w2 || !w3 || !w4) {
        free(w1); free(w2); free(w3); free(w4);
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter words: ");
    int read = scanf("%10s %10s %10s %10s", w1, w2, w3, w4);
    if (read != 4 || !is_upper_word(w1) || !is_upper_word(w2) || !is_upper_word(w3) || !is_upper_word(w4)) {
        printf("Incorrect input\n");
        free(w1); free(w2); free(w3); free(w4);
        return 1;
    }

    char **double_cross = NULL, **left_cross = NULL, **right_cross = NULL;
    int rc = create_double_leading_word_cross(w1, w2, w3, w4, &double_cross, &left_cross, &right_cross);

    free(w1); free(w2); free(w3); free(w4);

    if (rc == 1) {
        printf("Incorrect input\n");
        return 1;
    } else if (rc == 2) {
        printf("Unable to make two crosses\n");
        return 0;
    } else if (rc == 3) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    if (left_cross) {
        char **p = left_cross;
        while(*p) { printf("%s\n", *p); ++p; }
    }
    printf("\n");
    if (right_cross) {
        char **p = right_cross;
        while(*p) { printf("%s\n", *p); ++p; }
    }
    printf("\n");
    if (double_cross) {
        char **p = double_cross;
        while(*p) { printf("%s\n", *p); ++p; }
    }

    destroy(left_cross);
    destroy(right_cross);
    destroy(double_cross);

    return 0;
}
#endif

