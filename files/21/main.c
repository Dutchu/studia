#include <stdio.h>
<<<<<<< HEAD
#include <stdlib.h>
=======
>>>>>>> a1908a007bf558aa1b26fb6ddf3bcdbac0aaeb90

void readStdInput(char *path) {
    scanf("%30s", path);
}

void cleanStdInput(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

<<<<<<< HEAD
int readFile(FILE *fp_indexes, FILE *fp_letters) {
    int index;
    char ch;

    while (fscanf(fp_indexes, "%d", &index) > 0) {
//        printf("readFile: index = %d\n", index);
        fseek(fp_letters, index + 1, SEEK_SET);
        fscanf(fp_letters, "%c", &ch);
        printf("%c", ch);
    }

    return 1;
}

int corrupted(FILE *fp) {
    int ch;
    while ((ch = fgetc(fp)) != '\n') {
        if (ch >= 48 && ch <= 57 || ' ' == ch) {
        } else return 1;
    }
    rewind(fp);
    return 0;
}

int main() {
    FILE *fp_indexes;
    FILE *fp_letters;
//    char *path = "c:\\temp\\coded.txt";
=======
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
>>>>>>> a1908a007bf558aa1b26fb6ddf3bcdbac0aaeb90
    char path[31];
    printf("Podaj sciezke do pliku:");
    readStdInput(path);
    cleanStdInput();
<<<<<<< HEAD
    fp_indexes = fopen(path, "r");
    fp_letters = fopen(path, "r");

    if (fp_indexes == NULL) {
        if (fp_letters != NULL) {
            fclose(fp_letters);
        }
        printf("Couldn't open file\n");
        return 4;
    }

    /*if file corrupted*/
    if (corrupted(fp_indexes)) {
        printf("File corrupted\n");
        fclose(fp_indexes);
        fclose(fp_letters);
        return 6;
    }


    readFile(fp_indexes, fp_letters);

    fclose(fp_indexes);
    fclose(fp_letters);
=======
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
>>>>>>> a1908a007bf558aa1b26fb6ddf3bcdbac0aaeb90
    return (0);
}