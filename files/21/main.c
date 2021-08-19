#include <stdio.h>
#include <stdlib.h>

void readStdInput(char *path) {
    scanf("%30s", path);
}

void cleanStdInput(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

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
    char path[31];
    printf("Podaj sciezke do pliku:");
    readStdInput(path);
    cleanStdInput();
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
    return (0);
}