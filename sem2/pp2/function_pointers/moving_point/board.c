// board.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

static int is_board_valid(const struct board_t *b) {
    if (!b || !b->board || b->width <= 0 || b->height <= 0) return 0;
    return 1;
}

int create_board(struct board_t **out_board, int width, int height) {
    if (!out_board || width <= 0 || height <= 0) return 1;

    struct board_t *b = (struct board_t*)malloc(sizeof(struct board_t));
    if (!b) return 2;

    b->width = width;
    b->height = height;
    b->is_init = 0;
    b->player.x = 0;
    b->player.y = 0;

    b->move_player_up = move_player_up;
    b->move_player_down = move_player_down;
    b->move_player_left = move_player_left;
    b->move_player_right = move_player_right;

    b->board = (char**)malloc((size_t)height * sizeof(char*));
    if (!b->board) {
        free(b);
        return 2;
    }

    for (int i = 0; i < height; ++i) {
        *(b->board + i) = (char*)malloc((size_t)(width + 1) * sizeof(char));
        if (!(*(b->board + i))) {
            for (int j = 0; j < i; ++j) free(*(b->board + j));
            free(b->board);
            free(b);
            return 2;
        }
        memset(*(b->board + i), '.', (size_t)width);
        *(*(b->board + i) + width) = '\0';
    }

    *out_board = b;
    return 0;
}

void display_board(const struct board_t *board) {
    if (!is_board_valid(board)) return;
    for (int i = 0; i < board->height; ++i) {
        printf("%s\n", *(board->board + i));
    }
}

void free_board(struct board_t *board) {
    if (!board) return;
    if (board->board) {
        for (int i = 0; i < board->height; ++i) {
            free(*(board->board + i));
        }
        free(board->board);
    }
    free(board);
}

int set_player(struct board_t *board, int x, int y) {
    if (!is_board_valid(board)) return 1;
    if (board->is_init) return 1;
    if (x < 0 || x >= board->width || y < 0 || y >= board->height) return 1;

    board->player.x = x;
    board->player.y = y;
    *(*(board->board + y) + x) = '@';
    board->is_init = 1;
    return 0;
}

static struct board_t* do_move(struct board_t *board, int dx, int dy) {
    if (!is_board_valid(board) || !board->is_init) return NULL;

    int x = board->player.x;
    int y = board->player.y;

    if (x < 0 || y < 0 || x >= board->width || y >= board->height) {
        return NULL;
    }

    char *row = *(board->board + y);
    if (!row) return NULL;

    *(row + x) = '.';

    int nx = x + dx;
    int ny = y + dy;

    if (nx < 0) nx = board->width - 1;
    if (nx >= board->width) nx = 0;
    if (ny < 0) ny = board->height - 1;
    if (ny >= board->height) ny = 0;

    board->player.x = nx;
    board->player.y = ny;
    {
        char *row2 = *(board->board + ny);
        if (!row2) return NULL;
        *(row2 + nx) = '@';
    }

    return board;
}

struct board_t* move_player_up(struct board_t *board) {
    return do_move(board, 0, -1);
}

struct board_t* move_player_down(struct board_t *board) {
    return do_move(board, 0, 1);
}

struct board_t* move_player_left(struct board_t *board) {
    return do_move(board, -1, 0);
}

struct board_t* move_player_right(struct board_t *board) {
    return do_move(board, 1, 0);
}
