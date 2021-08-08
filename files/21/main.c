#include <stdio.h>

void readStdInput(char *path) {
    scanf("%30s", path);
}

void cleanStdInput(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int fSize(FILE *f) {
    if (f == NULL) {
        return -2;
    }

    long starting_position = ftell(f);

    if (fseek(f, 0L, SEEK_END) != 0) {
        return -1;
    }
    int file_size = ftell(f);

    fseek(f, starting_position, SEEK_SET);

    return file_size;
}

int readFile(FILE *fp, int f_pos, int inedx) {
    fseek(fp, inedx, SEEK_SET);
    printf("%c", fgetc(fp));
    return 1;
}

int readIndex(FILE *fp) {
    if (fp == NULL) { return -1; }

    int count = 0;
    int ch;

    int f_length = fSize(fp);
    while ((ch = fgetc(fp)) != '\n') {
        printf("char: %c\n", ch);
        readFile(fp, ftell(fp), ch);
        count++;
    }

    return count;
}

int main() {
    FILE *fp;
    char *path = "c:\\temp\\coded.txt";
/*
    char path[31];
    printf("Podaj sciezke do pliku:");
    readStdInput(path);
    cleanStdInput();
*/
    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Couldn't open file");
        return 4;
    }


    int f_pos = ftell(fp);
    printf("pozycja: %d\n", f_pos);

    readIndex(fp);

    fclose(fp);
    return (0);
}