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

int createFile(FILE *output_fp) {
    if (output_fp == NULL) { return -1; }

    int count = 0;

    while (count < 101) {
        fprintf(output_fp,"%d\n", count);
        count ++;
    }

    return count;
}



int main() {


//    char *output_path = "c:\\temp\\100.txt";

    char output_path[31];
    FILE *p_outFile;
    printf("Podaj sciezke do pliku wyjściowego:");
    readStdInput(output_path);

    p_outFile = fopen(output_path, "w");
    if (p_outFile == NULL) {
        printf("Couldn't create file\n");
        return 5;
    }
    cleanStdInput();

    if (createFile(p_outFile) == -1) {
        printf("Couldn't create file\n");
        return -1;
    } else {
        printf("File saved\n");
    }

    fclose(p_outFile);
    return (0);
}