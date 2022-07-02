#include <malloc.h>
#include "string.h"
#include "stdio.h"

#define FILE_PATH "C:\\Users\\Bartek\\Desktop\\studia\\sem2\\pp2\\structs\\18\\file"
#define BUFFER "C:\\Users\\Bartek\\Desktop\\studia\\sem2\\pp2\\structs\\18\\file.txt"
#define BUFFER_SIZE 1024
#define NUMBER_OF_FILES 5

int get_user_input(char *input);
int get_file_size(FILE *f_handle);

struct file_t {
    FILE *f;
    int size;
};

int main(int argc, char **vararg) {

    unsigned long read_count;
    unsigned long l_file_size;
    char *buffer;
    struct file_t temp_file;
    struct file_t **files_array;

    files_array = malloc(sizeof(struct file_t) * NUMBER_OF_FILES);

    for (int i = 0; i < NUMBER_OF_FILES; i++) {
        int file_size;
        char *file_number = calloc(1, sizeof(int));
        //prepare path to file
        char *path = (char *) calloc(1024, sizeof(char));
        strcat(path, FILE_PATH);
        itoa(i, file_number, 10);
        strcat(path, file_number);
        strcat(path, ".txt");
        //open file
        FILE *f_handle = fopen(path, "w+");
        //assign i-th file struct values
//        *(files_array + sizeof(struct file_t) * i) -> f = f_handle;
//        fwrite(file_number, sizeof(char), sizeof(file_number), f_handle);
        fprintf (f_handle, "%s",file_number);
        file_size = get_file_size(f_handle);
//        *(files_array + sizeof(struct file_t) * i) -> size = file_size;
        fclose(f_handle);
        free(path);
    }

    for (int i = 0; i < NUMBER_OF_FILES; i++) {
//        printf("Size    : %d, ", *(files_array + i * sizeof(struct file_t)) -> size);
//        printf("Pointer : %p\n", *(files_array + i * sizeof(struct file_t)) ->pafd f);
    }



//    for (int i = 0; i < NUMBER_OF_FILES; i++) {
//        l_file_size = get_file_size(files_array->f);
//        l_file_size = get_file_size(files_array->f);
//        printf("Size[%d] = %ld\n", i, l_file_size);
//    }
//
//    FILE *f_handle = fopen(FILE_PATH, "w+");
//    buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));
//    get_user_input(buffer);
//    printf("buffer:\n%s\n", buffer);
//
//    fwrite(BUFFER, sizeof(char), sizeof(BUFFER), f_handle);
//
//    read_count = fread(buffer, sizeof(char), l_file_size,f_handle);
//    printf("Read buffer:\n%s\n", buffer);
//    printf("count: %d\n", read_count);
//
//    if (f_handle != NULL) {
//        fputs("fopen example", f_handle);
//        fclose(f_handle);
//    } else {
//        printf("Something's fucky");
//    }

//    p_temp_file->f = f_handle;
//    p_temp_file->size = sizeof(BUFFER);

//    fclose(f_handle);
//
//    return 0;
//}
//
//int get_user_input(char *input) {
//    if (input == NULL) {
//        return 1;
//    }
//
//    scanf("%s", input);

    return 0;
}

int get_file_size(FILE *f_handle) {
    if (f_handle == NULL) {
        printf("Handle is null");
        return - 1;
    }
    unsigned long l_file_size = 0;

    // obtain file size:
    fseek (f_handle , 0 , SEEK_END);
    l_file_size = ftell (f_handle);
    rewind (f_handle);

    return (int) l_file_size;
}