#include <stdlib.h>

int main() {
    char *var = malloc(1);
    free(var);
    return 0;
}