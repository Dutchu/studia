#include <stdio.h>
#include <sys/stat.h>


void read_input(char *path) {
    scanf("%30s", path);
}

int file_size_from_path(const char *path){
    if(path==NULL) {return -2;}

    FILE *f;
    f=fopen(path,"r");
    if(f==NULL){return -1;}


    int rozmiar=0;
    int i=0;
    i=fgetc(f);

    while(i!=EOF){
        i=fgetc(f);
        rozmiar++;
        if(i==EOF){break;}
    }

    fclose(f);
    return rozmiar;
}

//int file_size_from_path(const char *path) {
//    if (path == NULL) {
//        return -2;
//    }
//
//    struct stat st;
//
//    if (stat(path, &st) == 0) {
//        return st.st_size;
//    } else {
//        printf("Unable to get file properties.\n");
//        printf("Please check whether '%s' file exists.\n", path);
//        return -1;
//    }
//}

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

int main() {

//    char *path = "c:\\temp\\test.txt";
    char path[31];
    printf("Podaj sciezke do pliku:");
    read_input(path);


    FILE *fp;
    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Couldn't open file");
        return 4;
    }


    int size_from_path = file_size_from_path(path);
    int size_from_file = file_size_from_file(fp);



    if (size_from_path < 0 || size_from_file < 0) {
        printf("Couldn't open file");
        fclose(fp);
        return 4;
    }

    if (size_from_file == size_from_path) {
        printf("Rozmiar pliku wynosi %d bajtow", size_from_path);
    }


    fclose(fp);
    return (0);
}