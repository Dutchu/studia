#include <stdio.h>
//#define BUFFER_SIZE 31

void readStdInput(char *path) {
    scanf("%30s", path);
}

int main() {
    FILE *fp;
//    char* path = "c:\\temp\\test.txt";
    char path[31];
    printf("Podaj sciezke do pliku:");
    readStdInput(path);

    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Couldn't open file");

        return 4;
    }
    if (getc(fp) == EOF) {
        printf("nothing to show");
        fclose(fp);
        return 0;
    }
    rewind(fp);

    do {
        // Taking input single character at a time
        char c = (char) fgetc(fp);

        // Checking for end of file
        if (feof(fp))
            break;

        printf("%c", c);
    } while (1);

    fclose(fp);
    return (0);
}