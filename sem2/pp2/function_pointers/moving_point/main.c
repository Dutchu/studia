#include <stdio.h>
#include <stdlib.h>
#include "board.h"

int main(void) {
    int width = 0, height = 0;

    printf("Enter width and height of the board: ");
    if (scanf("%d %d", &width, &height) != 2) {
        printf("Incorrect input\n");
        return 1;
    }
    if (width <= 0 || height <= 0) {
        printf("Incorrect input data\n");
        return 2;
    }

    struct board_t *board = NULL;
    int cr = create_board(&board, width, height);
    if (cr == 2) {
        printf("Failed to allocate memory\n");
        return 8;
    } else if (cr != 0) {
        printf("Incorrect input data\n");
        return 2;
    }

    int x = 0, y = 0;
    printf("Enter player's initial coordinates (x, y): ");
    if (scanf("%d %d", &x, &y) != 2) {
        printf("Incorrect input\n");
        free_board(board);
        return 1;
    }
    if (x < 0 || x >= width || y < 0 || y >= height) {
        printf("Incorrect input data\n");
        free_board(board);
        return 2;
    }
    if (set_player(board, x, y) != 0) {
        printf("Incorrect input data\n");
        free_board(board);
        return 2;
    }

    display_board(board);

    for (;;) {
        printf("Choose your action: ");
        char action = 0;
        if (scanf(" %c", &action) != 1) {
            printf("Incorrect input\n");
            free_board(board);
            return 1;
        }
        if (action == 'q') {
            break;
        } else if (action == 'w') {
            board->move_player_up(board);
            display_board(board);
        } else if (action == 's') {
            board->move_player_down(board);
            display_board(board);
        } else if (action == 'a') {
            board->move_player_left(board);
            display_board(board);
        } else if (action == 'd') {
            board->move_player_right(board);
            display_board(board);
        } else {
            printf("Incorrect choice\n");
        }
    }

    free_board(board);
    return 0;
}

