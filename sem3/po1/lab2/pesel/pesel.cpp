#include <stdio.h>

int isprime(int num)
{
    int primeflag = 1;
    for (int i = 2; i < num / 2; i++) {
        if (num % i == 0) {
            printf("For i = %d there was no remainder\n", i);
            primeflag = 0;
        }
    }
    return primeflag;
}


int main()
{
    int input;
    printf("Gibe me number: ");
    scanf("%d", &input);
    if (isprime(input))
    {
        printf("%d Is a pesel\n", input);
    } else {
        printf("%d Is not a pesel\n", input);
    }
    
    return 0;
}