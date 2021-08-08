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

int fsize(FILE *f) {
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

int copyFile(FILE *input_fp, FILE *output_fp) {
    if (input_fp == NULL || output_fp == NULL) { return -1; }

    int count = 0;

    int flength = fsize(input_fp);
    for (int fpos = flength - 1; fpos >= 0; fpos--) {
        fseek(input_fp, fpos, SEEK_SET);
        fputc(fgetc(input_fp), output_fp);
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