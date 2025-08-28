#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int load_maze(const char *filename, char ***labirynth);

int solve_maze(char **maze, int x, int y);

void free_maze(char **maze);


void print_maze(char **maze);

int solve_maze_recursive(char **maze, int rows, int cols, int x, int y);


void free_maze(char **maze) {
    if (maze == NULL) {
        return;
    }
    for (int i = 0; *(maze + i) != NULL; ++i) {
        free(*(maze + i));
    }
    free(maze);
}

void print_maze(char **maze) {
    if (maze == NULL) {
        return;
    }
    for (int i = 0; *(maze + i) != NULL; ++i) {
        printf("%s\n", *(maze + i));
    }
}

int load_maze(const char *filename, char ***labirynth) {
    if (filename == NULL || labirynth == NULL) {
        return 1;
    }

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        return 2;
    }

    int rows = 0, cols = 0;
    int current_cols = 0;
    char c;

    
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {
            if (rows == 0) {
                cols = current_cols;
            } else if (current_cols != cols) {
                fclose(f);
                return 3; 
            }
            rows++;
            current_cols = 0;
        } else {
            current_cols++;
        }
    }
    
    if (current_cols > 0) {
        if (rows == 0) {
            cols = current_cols;
        } else if (current_cols != cols) {
            fclose(f);
            return 3;
        }
        rows++;
    }

    if (rows == 0 || cols == 0) {
        fclose(f);
        return 3;
    }

    
    *labirynth = (char **)malloc((rows + 1) * sizeof(char *));
    if (*labirynth == NULL) {
        fclose(f);
        return 4;
    }

    for (int i = 0; i < rows; ++i) {
        *(*labirynth + i) = (char *)malloc((cols + 1) * sizeof(char));
        if (*(*labirynth + i) == NULL) {
            *(*labirynth + i) = NULL;
            free_maze(*labirynth);
            *labirynth = NULL;
            fclose(f);
            return 4;
        }
    }

    rewind(f);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            *(*(*labirynth + i) + j) = fgetc(f);
        }
        *(*(*labirynth + i) + cols) = '\0';
        fgetc(f); 
    }

    *(*labirynth + rows) = NULL;

    fclose(f);
    return 0;
}

int solve_maze_recursive(char **maze, int rows, int cols, int x, int y) {
    if (y < 0 || y >= rows || x < 0 || x >= cols) {
        return 0;
    }
    char current_cell = *(*(maze + y) + x);
    if (current_cell == 'b') return 1;
    if (current_cell == '#' || current_cell == '*') return 0;

    *(*(maze + y) + x) = '*';

    if (solve_maze_recursive(maze, rows, cols, x, y - 1)) return 1;
    if (solve_maze_recursive(maze, rows, cols, x + 1, y)) return 1;
    if (solve_maze_recursive(maze, rows, cols, x, y + 1)) return 1;
    if (solve_maze_recursive(maze, rows, cols, x - 1, y)) return 1;

    *(*(maze + y) + x) = ' ';
    return 0;
}

int solve_maze(char **maze, int x, int y) {
    if (maze == NULL || *maze == NULL) {
        return -1;
    }
    
    int cols = strlen(*maze);
    int rows = 0;
    while (*(maze + rows) != NULL) {
        rows++;
    }

    int start_count = 0;
    int end_count = 0;
    for (int i = 0; i < rows; ++i) {
        
        if (strlen(*(maze + i)) != (size_t)cols) {
            return -1; 
        }
        
        for (int j = 0; j < cols; ++j) {
            char cell = *(*(maze + i) + j);
            if (cell == 'a') start_count++;
            if (cell == 'b') end_count++;
        }
    }
    
    if (start_count != 1 || end_count != 1) {
        return -1;
    }
    
    if (y < 0 || y >= rows || x < 0 || x >= cols) {
        return -1;
    }

    int success = solve_maze_recursive(maze, rows, cols, x, y);

    *(*(maze + y) + x) = 'a';

    return success;
}
int main() {

    char *filename = (char *) malloc(31 * sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter filename: ");
    scanf("%30s", filename);

    char **maze = NULL;
    int err = load_maze(filename, &maze);

    if (err != 0) {
        free(filename);
        switch (err) {
            case 2:
                printf("Couldn't open file\n");
                return 4;
            case 3:
                printf("File corrupted\n");
                return 6;
            case 4:
                printf("Failed to allocate memory\n");
                return 8;
        }
    }

    int start_x = -1, start_y = -1;
    int rows = 0;
    for (int i = 0; *(maze + i) != NULL; ++i) {
        rows++;
        for (int j = 0; *(*(maze + i) + j) != '\0'; ++j) {
            if (*(*(maze + i) + j) == 'a') {
                start_y = i;
                start_x = j;
            }
        }
    }

    int maze_result, status_code = 0;
    maze_result = solve_maze(maze, start_x, start_y);
    switch (maze_result) {
        case 1:
            print_maze(maze);
            break;
        case 0:
            printf("Couldn't find path\n");
            break;
        case -1:
            printf("File corrupted\n");
            status_code = 6;
            break;
        default:
            printf("idk what happened xD\n");
    }

    free(filename);
    free_maze(maze);

    return status_code;
}