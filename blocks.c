#include "blocks.h"
#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

All_Recs_t *allocAllPieces(void) {
  All_Recs_t *all_pieces = (All_Recs_t *)malloc(sizeof(All_Recs_t));
  if (all_pieces == NULL) {
    fprintf(stderr, "ERROR COULD NOT CREATE ALL_PIECES \n");
    return NULL;
  }
  all_pieces->len = 0;
  size_t capacity =
      GetScreenWidth() * GetScreenHeight() / (BLOCK_SIZE * BLOCK_SIZE);
  all_pieces->cap = capacity;
  all_pieces->all = malloc(sizeof(Rectangle *) * all_pieces->cap);
  for (size_t i = 0; i < all_pieces->cap; i++) {
    all_pieces->all[i] = malloc(sizeof(Rectangle));
  }

  return all_pieces;
}

piece_t *create_piece(void) {
  Vector2 initial_pos = {.x = GetScreenWidth() / 2.0, .y = 0.0};
  enum piece_name p_n = (rand() % 7); // THE number of pieces is 7
  piece_t *piece = malloc(sizeof(piece_t));
  if (piece == NULL) {
    fprintf(stderr, "ERROR COULD NOT CREATE PIECE \n");
    return NULL;
  }
  piece->active = false;
  piece->piece_name = p_n;
  piece->block[0].x = initial_pos.x;
  piece->block[0].y = initial_pos.y;
  switch (p_n) {
  case T:
    piece->dir = UP;
    // block[1] is under block[0]
    piece->block[1].x = piece->block[0].x;
    piece->block[1].y = piece->block[0].y + BLOCK_SIZE;

    // block[2] is on the left of block[1]
    piece->block[2].x = piece->block[1].x - BLOCK_SIZE;
    piece->block[2].y = piece->block[1].y;
    // block[3] is on the right of block[1]
    piece->block[3].x = piece->block[1].x + BLOCK_SIZE;
    piece->block[3].y = piece->block[1].y;
    // each pice has a color
    piece->p_color = RED;
    break;
  case Square:
    piece->dir = UP;
    // block[1] is under block[0]
    piece->block[1].x = piece->block[0].x;
    piece->block[1].y = piece->block[0].y + BLOCK_SIZE;
    // block[2] is on the left of block[1]
    piece->block[2].x = piece->block[1].x - BLOCK_SIZE;
    piece->block[2].y = piece->block[1].y;
    // block[3] is on top of block[2]
    piece->block[3].x = piece->block[2].x;
    piece->block[3].y = piece->block[2].y - BLOCK_SIZE;
    // each pice has a color
    piece->p_color = GREEN;
    break;
  case Stick:
    piece->dir = UP;
    // block[1] is under block[0]
    piece->block[1].x = piece->block[0].x;
    piece->block[1].y = piece->block[0].y + BLOCK_SIZE;
    // block[2] is under block[1]
    piece->block[2].x = piece->block[1].x;
    piece->block[2].y = piece->block[1].y + BLOCK_SIZE;
    // block[3] is under block[2]
    piece->block[3].x = piece->block[2].x;
    piece->block[3].y = piece->block[2].y + BLOCK_SIZE;
    // each pice has a color
    piece->p_color = BLUE;
    break;
  case L_left:
    piece->dir = LEFT;
    // block[1] is on the right of block[0]
    piece->block[1].x = piece->block[0].x + BLOCK_SIZE;
    piece->block[1].y = piece->block[0].y;
    // block[2] is on top of block[1]
    piece->block[2].x = piece->block[1].x;
    piece->block[2].y = piece->block[1].y - BLOCK_SIZE;
    // block[3] is on the top of block[2]
    piece->block[3].x = piece->block[2].x;
    piece->block[3].y = piece->block[2].y - BLOCK_SIZE;
    // each pice has a color
    piece->p_color = YELLOW;
    break;
  case L_right:
    piece->dir = RIGHT;
    // block[1] is on the left block[0]
    piece->block[1].x = piece->block[0].x - BLOCK_SIZE;
    piece->block[1].y = piece->block[0].y;
    // block[2] is on top of block[1]
    piece->block[2].x = piece->block[1].x;
    piece->block[2].y = piece->block[1].y - BLOCK_SIZE;
    // block[3] is on top of block[2]
    piece->block[3].x = piece->block[2].x;
    piece->block[3].y = piece->block[2].y - BLOCK_SIZE;
    // each pice has a color
    piece->p_color = ORANGE;
    break;
  case Dog_left:
    piece->dir = LEFT;
    // block[1] is on the right of block[0]
    piece->block[1].x = piece->block[0].x + BLOCK_SIZE;
    piece->block[1].y = piece->block[0].y;
    // block[2] is under block[1]
    piece->block[2].x = piece->block[0].x;
    piece->block[2].y = piece->block[0].y + BLOCK_SIZE;
    // block[3] is on the right of block[2]
    piece->block[3].x = piece->block[2].x + BLOCK_SIZE;
    piece->block[3].y = piece->block[2].y;
    // each pice has a color
    piece->p_color = BLUE;
    break;
  case Dog_right:
    piece->dir = RIGHT;
    // block[1] is on the left of block[0]
    piece->block[1].x = piece->block[0].x - BLOCK_SIZE;
    piece->block[1].y = piece->block[0].y;
    // block[2] is under block[1]
    piece->block[2].x = piece->block[0].x;
    piece->block[2].y = piece->block[0].y + BLOCK_SIZE;
    // block[3] is on the left of block[2]
    piece->block[3].x = piece->block[2].x - BLOCK_SIZE;
    piece->block[3].y = piece->block[2].y;
    // each pice has a color
    piece->p_color = VIOLET;
    break;
  }
  // each has consist of 4 rectangle of size BLOCK_SIZE
  for (size_t i = 0; i < 4; i++) {
    piece->block[i].height = BLOCK_SIZE;
    piece->block[i].width = BLOCK_SIZE;
  }
  return piece;
}

// void update_piece_pos(piece_t *piece) {}

void draw_piece(piece_t *piece) {
  for (int i = 0; i < 4; i++) {
    DrawRectangleRec(piece->block[i], piece->p_color);
  }
}

void free_All_pieces(All_Recs_t *all_pieces) {
  for (size_t i = 0; i < all_pieces->cap; i++) {
    free(all_pieces->all[i]);
  }
  free(all_pieces);
}
