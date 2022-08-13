
#include "string.h"
#include "stdio.h"
#include "struct_utils.h"

int main() {

    int size = sizeof(struct message_t);
    int c_size = sizeof(char );
    int d_size = sizeof(double );
    int i_size = sizeof(int);
    printf("struct size : %d\n", size);
    printf("sum size : %d\n", c_size + d_size + i_size);

    struct message_t arr_mess[100];

    printf("first address  : %p\n", (arr_mess + 0) );
    printf("second address : %p\n", (arr_mess + 1) );
    printf("difference : %x\n", (arr_mess + 1) - (arr_mess + 0) );

    int address1 = (int) arr_mess;
    int address2 = (int) (arr_mess + 1);
    printf("address in int : %x\n", address1);
    printf("address in int : %x\n", address2);
    printf("diff : %x\n", address2 - address1);

    printf("address in int : %x\n", address1);
    printf("address of \"a\" of arr[%d] : %x\n", 0, &((arr_mess + 0)->a) );
    printf("address of \"b\" of arr[%d] : %x\n", 0, &((arr_mess + 0)->b) );
    printf("address of \"c\" of arr[%d] : %x\n", 0, &((arr_mess + 0)->c) );

    printf("address in int : %x\n", address2);
    printf("address of \"a\" of arr[%d] : %x\n", 1, &((arr_mess + 1)->a) );
    printf("address of \"b\" of arr[%d] : %x\n", 1, &((arr_mess + 1)->b) );
    printf("address of \"c\" of arr[%d] : %x\n", 1, &((arr_mess + 1)->c) );

    for(int i = 0; i < 100; i++) {
        ((arr_mess + i)->a) = '1';
        ((arr_mess + i)->b) = 49.0;
        ((arr_mess + i)->c) = 50;

        char *free_space1 = &((arr_mess + i)->a) + 1;
        *(free_space1 + 0) =  's';
        *(free_space1 + 1) =  'e';
        *(free_space1 + 2) =  'x';
        *(free_space1 + 3) =  'y';
        *(free_space1 + 4) =  's';
        *(free_space1 + 5) =  'e';
        *(free_space1 + 6) =  'x';

        char *free_space2 = (char *) &((arr_mess + i)->c) + 4;

        *(free_space2 + 0) =  's';
        *(free_space2 + 1) =  'e';
        *(free_space2 + 2) =  'x';
        *(free_space2 + 3) =  'y';
    }


    int offset = 50;
    printf("address in int : %x\n", (arr_mess + offset));
    printf("address of \"a\" of arr[%d] : %x\n", offset, &((arr_mess + offset)->a) );
    printf("address of \"b\" of arr[%d] : %x\n", offset, &((arr_mess + offset)->b) );
    printf("address of \"c\" of arr[%d] : %x\n", offset, &((arr_mess + offset)->c) );

    printf("address in int : %x\n", (arr_mess + offset));

    for(int i = 0; i < 24; i++) {
        printf("%c", *((&((arr_mess + offset)->a) + 0) + i)  );
    }
    printf("\na = %c, b = %lf, c = %d\n", (arr_mess + offset)->a, (arr_mess + offset)->b, (arr_mess + offset)->c);


    int result;
    result = load_data(arr_mess, 100, "xd.txt");
    if (result < 0) printf("Aj, kurwa!");
    printf("%d", result);

    return 0;
}
