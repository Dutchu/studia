#include <stdio.h>


int read_file(const char *filename) {
    int files_count = 0;
    char next_filename[31];

    if (filename == NULL) {
        return -1;
    }

    FILE *fp;
    fp = fopen(filename, "r");

    if (fp != NULL) {
        files_count = 1;
        while (fscanf(fp, "%30s", next_filename) != EOF) {

            printf("%s\n", next_filename);

            files_count = read_file(next_filename) + files_count;
        }
        fclose(fp);

    }
    return files_count;
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

int main() {

//    char *path = "c:\\temp\\coded.txt";
    char path[31];
    int files_red;
    printf("Podaj sciezke do pliku:\n");
    readStdInput(path);
    cleanStdInput();
    files_red = read_file(path);
    if (files_red == 0)  {
        printf("couldn't open file");
        return 4;
    }
    printf("%d", files_red);
    return 0;
}
