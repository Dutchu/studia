#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <alloca.h>


int multiply(const char *number1, const char *number2, char **result);

int subtract(const char *number1, const char *number2, char **result);

int add(const char *number1, const char *number2, char **result);

int validate(const char *number);

int validate_expression(const char *expr);

int calculate(const char *expr, char **result);


void reverse_string(char *str) {
    if (!str) return;
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        char temp = *(str + i);
        *(str + i) = *(str + len - i - 1);
        *(str + len - i - 1) = temp;
    }
}

int compare_magnitude(const char *num1, const char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;
    return strcmp(num1, num2);
}

char *strip_leading_zeros(char *num) {
    if (!num) return NULL;
    int len = strlen(num);
    if (len <= 1) return num;
    int first_digit = 0;
    while (first_digit < len - 1 && *(num + first_digit) == '0') {
        first_digit++;
    }
    if (first_digit > 0) {
        memmove(num, num + first_digit, len - first_digit + 1);
    }
    return num;
}


int validate(const char* number) {
    if (number == NULL) {
        return -1;
    }

    int len = strlen(number);
    if (len == 0) {
        return 2;
    }

    const char *p = number;
    if (*p == '+' || *p == '-') {
        p++; 
    }
    if (*p == '\0') {
        return 2; 
    }
    if (*p == '0' && *(p + 1) != '\0') {
        return 2;
    }
    while (*p != '\0') {
        if (!isdigit(*p)) {
            return 2;
        }
        p++;
    }

    return 0; 
}

int add(const char *number1, const char *number2, char **result) {
    if (!number1 || !number2 || !result) return 1;
    if (validate(number1) != 0 || validate(number2) != 0) return 2;

    int sign1 = (*number1 == '-');
    int sign2 = (*number2 == '-');
    const char *n1_abs = sign1 ? number1 + 1 : number1;
    const char *n2_abs = sign2 ? number2 + 1 : number2;

    char *temp_res_str;

    if (sign1 == sign2) {
        int len1 = strlen(n1_abs);
        int len2 = strlen(n2_abs);
        int max_len = (len1 > len2) ? len1 : len2;
        char *res_rev = alloca(max_len + 2);

        char *n1_rev = alloca(len1 + 1);
        strcpy(n1_rev, n1_abs);
        reverse_string(n1_rev);

        char *n2_rev = alloca(len2 + 1);
        strcpy(n2_rev, n2_abs);
        reverse_string(n2_rev);

        int carry = 0, i = 0;
        for (i = 0; i < max_len; ++i) {
            int d1 = (i < len1) ? (*(n1_rev + i) - '0') : 0;
            int d2 = (i < len2) ? (*(n2_rev + i) - '0') : 0;
            int sum = d1 + d2 + carry;
            *(res_rev + i) = (sum % 10) + '0';
            carry = sum / 10;
        }
        if (carry) *(res_rev + i++) = '1';
        *(res_rev + i) = '\0';

        reverse_string(res_rev);
        temp_res_str = res_rev;

        int final_len = strlen(temp_res_str);
        *result = (char *) malloc(final_len + 1 + sign1);
        if (!*result) return 3;

        if (sign1 && strcmp(temp_res_str, "0") != 0) {
            *(*result) = '-';
            strcpy(*result + 1, temp_res_str);
        } else {
            strcpy(*result, temp_res_str);
        }
    } else {
        int cmp = compare_magnitude(n1_abs, n2_abs);
        if (cmp == 0) {
            *result = (char *) malloc(2);
            if (!*result) return 3;
            strcpy(*result, "0");
            return 0;
        }

        const char *larger = (cmp > 0) ? n1_abs : n2_abs;
        const char *smaller = (cmp < 0) ? n1_abs : n2_abs;

        int len_l = strlen(larger);
        int len_s = strlen(smaller);
        char *res_rev = alloca(len_l + 1);

        char *larger_rev = alloca(len_l + 1);
        strcpy(larger_rev, larger);
        reverse_string(larger_rev);

        char *smaller_rev = alloca(len_s + 1);
        strcpy(smaller_rev, smaller);
        reverse_string(smaller_rev);

        int borrow = 0, i = 0;
        for (i = 0; i < len_l; ++i) {
            int d1 = *(larger_rev + i) - '0';
            int d2 = (i < len_s) ? (*(smaller_rev + i) - '0') : 0;
            int diff = d1 - d2 - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            *(res_rev + i) = diff + '0';
        }
        *(res_rev + i) = '\0';
        reverse_string(res_rev);
        temp_res_str = strip_leading_zeros(res_rev);

        int result_is_neg = (cmp < 0 && !sign1) || (cmp > 0 && sign1);
        int final_len = strlen(temp_res_str);

        *result = (char *) malloc(final_len + 1 + result_is_neg);
        if (!*result) return 3;

        if (result_is_neg) {
            *(*result) = '-';
            strcpy(*result + 1, temp_res_str);
        } else {
            strcpy(*result, temp_res_str);
        }
    }
    return 0;
}

int subtract(const char *number1, const char *number2, char **result) {
    if (!number1 || !number2 || !result) return 1;
    if (validate(number1) != 0 || validate(number2) != 0) return 2;

    int len2 = strlen(number2);
    char *negated_n2 = alloca(len2 + 2);

    if (*number2 == '-') {
        strcpy(negated_n2, number2 + 1);
    } else {
        *negated_n2 = '-';
        strcpy(negated_n2 + 1, number2);
    }

    return add(number1, negated_n2, result);
}

int multiply(const char *number1, const char *number2, char **result) {
    if (!number1 || !number2 || !result) return 1;
    if (validate(number1) != 0 || validate(number2) != 0) return 2;

    int sign1 = (*number1 == '-');
    int sign2 = (*number2 == '-');
    const char *n1_abs = sign1 ? number1 + 1 : number1;
    const char *n2_abs = sign2 ? number2 + 1 : number2;

    if (strcmp(n1_abs, "0") == 0 || strcmp(n2_abs, "0") == 0) {
        *result = (char *) malloc(2);
        if (!*result) return 3;
        strcpy(*result, "0");
        return 0;
    }

    int len1 = strlen(n1_abs);
    int len2 = strlen(n2_abs);
    int res_len = len1 + len2;
    int *res_int = alloca(res_len * sizeof(int));
    memset(res_int, 0, res_len * sizeof(int));

    int i_n1 = 0, i_n2 = 0;
    for (int i = len1 - 1; i >= 0; i--) {
        int carry = 0;
        int d1 = *(n1_abs + i) - '0';
        i_n2 = 0;
        for (int j = len2 - 1; j >= 0; j--) {
            int d2 = *(n2_abs + j) - '0';
            int sum = d1 * d2 + *(res_int + i_n1 + i_n2) + carry;
            carry = sum / 10;
            *(res_int + i_n1 + i_n2) = sum % 10;
            i_n2++;
        }
        if (carry > 0) *(res_int + i_n1 + i_n2) += carry;
        i_n1++;
    }

    int i = res_len - 1;
    while (i >= 0 && *(res_int + i) == 0) i--;

    int result_sign = (sign1 != sign2);
    *result = (char *) malloc(i + 2 + result_sign);
    if (!*result) return 3;

    int k = 0;
    if (result_sign) *((*result) + k++) = '-';
    while (i >= 0) *((*result) + k++) = *(res_int + i--) + '0';
    *(*result + k) = '\0';

    return 0;
}

int validate_expression(const char* expr) {
    if (expr == NULL || *expr == '\0') {
        return 1; 
    }

    const char *p = expr;

    if (*p == '-') {
        p++;
    }
    
    if (!isdigit(*p)) {
        return 1; 
    }
    while (isdigit(*p)) {
        p++;
    }
    
    while (*p != '\0') {
        
        if (*p != '+' && *p != '-' && *p != '*') {
            return 1;
        }
        p++; 

        if (*p == '+') {
            return 1; 
        }
        if (*p == '-') {
            p++;
        }
        if (!isdigit(*p)) {
            return 1; 
        }
        while (isdigit(*p)) {
            p++;
        }
    }
    return 0;
}

int calculate(const char *expr, char **result) {
    if (!expr || !result) return 1;
    if (validate_expression(expr) != 0) return 2;

    const char *p = expr;
    char *current_result = NULL;
    char *operand = NULL;
    char op = 0;
    int err = 0;

    const char *num_start = p;
    if (*p == '+' || *p == '-') p++;
    while (isdigit(*p)) p++;
    int len = p - num_start;
    current_result = (char *) malloc(len + 1);
    if (!current_result) return 3;
    strncpy(current_result, num_start, len);
    *(current_result + len) = '\0';

    while (*p != '\0') {
        op = *p++;
        num_start = p;
        if (*p == '+' || *p == '-') p++;
        while (isdigit(*p)) p++;
        len = p - num_start;
        operand = (char *) malloc(len + 1);
        if (!operand) {
            free(current_result);
            return 3;
        }
        strncpy(operand, num_start, len);
        *(operand + len) = '\0';

        char *next_result = NULL;
        switch (op) {
            case '+':
                err = add(current_result, operand, &next_result);
                break;
            case '-':
                err = subtract(current_result, operand, &next_result);
                break;
            case '*':
                err = multiply(current_result, operand, &next_result);
                break;
        }

        free(current_result);
        free(operand);
        operand = NULL;

        if (err != 0) {
            if (next_result) free(next_result);
            return 3;
        }
        current_result = next_result;
    }

    *result = current_result;
    return 0;
}

int main() {
    char *expr = (char *) malloc(501);
    if (!expr) {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj wyrazenie: ");
    if (scanf("%500s", expr) != 1) {
        printf("Incorrect input\n");
        free(expr);
        return 1;
    }

    char *result = NULL;
    int err_code = calculate(expr, &result);

    if (err_code == 2) {
        printf("Incorrect input\n");
        free(expr);
        return 1;
    } else if (err_code == 3) {
        printf("Failed to allocate memory");
        free(expr);
        if (result) free(result);
        return 8;
    }

    printf("%s\n", result);

    free(expr);
    free(result);

    return 0;
}