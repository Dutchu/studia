
#include "string.h"
#include "stdio.h"
#include "struct_utils.h"

int main() {

    struct file_t files[FILES_NUMBER];

    int loop = 0;
    int files_opened = 0;
    printf("Enter file names: ");
    while (1) {

        char buffer[FILE_NAME_BUFFER_SIZE * sizeof(char) + 1] = {0};

        fgets(buffer, FILE_NAME_BUFFER_SIZE, stdin);
        if (*buffer == '\n') {

            break;
        }

        char *pos;
        if ((pos = strchr(buffer, '\n')) != NULL) {
            *pos = '\0';
        }

        int result;
        result = open_file((files + files_opened), buffer);
        if (result != 1 && result != 2) {
            if (files_opened < FILES_NUMBER) {
                files_opened++;
            }
        }

        loop++;
    }

    if (files_opened == 0) {
        printf("Couldn't open file");
        return 4;
    }

    struct file_t *file;
    int files_written = 0;
    printf("Podaj teksty: ");
    while (1) {
        char buffer[FILE_NAME_BUFFER_SIZE * sizeof(char) + 1] = {0};

        if (fgets(buffer, FILE_NAME_BUFFER_SIZE, stdin) == NULL) {
        }
        if (*buffer == '\n') {
            break;
        }

        file = find_min(files, files_opened);
        if (file == NULL) {
            printf("Failed to find smallest file");
        }

        size_t size_written = fwrite(buffer, sizeof(char), strlen(buffer), file->f);
        file->size = file->size + (int) size_written;
        files_written++;
    }

    for (int i = 0; i < files_opened; i++) {
        close_file((files + i));
    }

    printf("Files saved");
    return 0;
}
