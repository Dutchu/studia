#include <stdio.h>


void read_input(char *path) {
    scanf("%30s", path);
}

void clean_stdin(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int copyFile(FILE *input_fp, FILE *output_fp) {
    if (input_fp == NULL || output_fp == NULL) { return -1; }


    int count = 0;
    int ch;

    /* Copy file contents character by character. */
    while ((ch = fgetc(input_fp)) != EOF) {
        fputc(ch, output_fp);
        /* Increment character copied count */
        count++;
    }

    return count;

}

int main() {

//    char *input_path = "c:\\temp\\in.txt";
//    char *output_path = "c:\\temp\\out.txt";
    char input_path[31];
    char output_path[31];
    FILE *p_inFile;
    FILE *p_outFile;

    printf("Podaj sciezke do pliku:");
    read_input(input_path);
    p_inFile = fopen(input_path, "r");
    if (p_inFile == NULL) {
        printf("Couldn't open file\n");
        return 4;
    }
    clean_stdin();

    printf("Podaj sciezke do pliku wyjściowego:");
    read_input(output_path);
    p_outFile = fopen(output_path, "w");
    if (p_outFile == NULL) {
        printf("Couldn't create file\n");
        fclose(p_inFile);
        return 5;
    }
    clean_stdin();

    if (copyFile(p_inFile, p_outFile) == -1) {
        printf("Error while coping file\n");
        return -1;
    } else {
        printf("File copied\n");
    }


    fclose(p_inFile);
    fclose(p_outFile);
    return (0);
}