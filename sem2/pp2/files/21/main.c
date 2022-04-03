#include <stdio.h>

int file_size_from_file(FILE *f) {

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
        fseek(fp_letters, index, SEEK_SET);
        fscanf(fp_letters, "%c", &ch);
        printf("%c", ch);
    }

    return 1;
}

int corruptedNumbers(FILE *fp) {

    int ch;
    while ((ch = fgetc(fp)) != '\n') {
        if (ch >= 48 && ch <= 57 || ' ' == ch) {
        } else return 1;
    }
    rewind(fp);
    return 0;
}

int corruptedIndexes(FILE *fp) {
    int min = 9999;
    int max = -9999;
    int tmp;

    while (fscanf(fp, "%d", &tmp) > 0) {
        if (max < tmp) max = tmp;
        if (min > tmp) min = tmp;
//        printf("corruptedIndexes:\n- tmp = %d\n- min = %d\n- max = %d\n", tmp, min, max);
    }

//    printf("corruptedIndexes [if]: ftell(fp)=%d > min=%d || file_size_from_file(fp)=%d < max=%d\n", ftell(fp), min, file_size_from_file(fp)-1, max);
    if (ftell(fp) > min || max > file_size_from_file(fp) -1) {
//        printf("corruptedIndexes [if]: ftell(fp)=%d > min=%d || file_size_from_file(fp)=%d < max=%d\n", ftell(fp), min, file_size_from_file(fp)-1, max);
        rewind(fp);
        return 1;
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

    /*if file corruptedNumbers*/
    if (corruptedNumbers(fp_indexes)) {
        printf("File corrupted\n");
        fclose(fp_indexes);
        fclose(fp_letters);
        return 6;
    }

    if (corruptedIndexes(fp_indexes)) {
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