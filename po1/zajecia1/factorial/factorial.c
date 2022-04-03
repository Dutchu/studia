#include <stdio.h>

int factorial(int num) {
     if(num <= 1) {
          return 1;
     } else if (num > 19) {
          printf("Lepiej nie byczq\n");
          return 1;
     }
     num = num * factorial(num -1);
     return num;
}

int main() {
     int result, input;
     printf("Gib number: ");
     scanf("%d", &input);
     result = factorial(input);
     printf("Factorial: %d\n", result);
}