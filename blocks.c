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
  all_pieces->all = malloc(sizeof(Rec_with_color_t *) * all_pieces->cap);
  for (size_t i = 0; i < all_pieces->cap; i++) {
    all_pieces->all[i] = malloc(sizeof(Rec_with_color_t));
  }

  return all_pieces;
}

void create_piece(piece_t *piece) {
  Vector2 initial_pos = {.x = GetScreenWidth() / 2.0, .y = 0.0};
  enum piece_name p_n = (rand() % 7); // THE number of pieces is 7
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
}

bool update_piece_pos(piece_t *piece, KeyboardKey key, float speed) {
  float closest_to_floor = piece->block[0].y;
  float closest_to_right_border = piece->block[0].x;
  float closest_to_left_border = piece->block[0].x;
  for (size_t j = 0; j < 4; j++) {
    if (piece->block[j].x >= closest_to_right_border) {
      closest_to_right_border = piece->block[j].x;
    }
    if (piece->block[j].x <= closest_to_left_border) {
      closest_to_left_border = piece->block[j].x;
    }
    if (piece->block[j].y >= closest_to_floor) {
      closest_to_floor = piece->block[j].y;
    }
  }
  bool reached_floor = (closest_to_floor == (GetScreenHeight() - BLOCK_SIZE));

  bool reached_left_border =
      (closest_to_left_border - BLOCK_SIZE / 10.0) < EPSILON;
  // bool reached_right_border =
  //     (closest_to_right_border -
  //          1.0 * (GetScreenWidth() - (BLOCK_SIZE / 10.0)) <
  //      EPSILON);
  bool reached_right_border = (GetScreenWidth() - (1.0 * BLOCK_SIZE / 10.0) -
                               closest_to_right_border) < EPSILON;
  // update piece pos
  //
  // KEY_RIGHT           = 262,      // Key: Cursor right
  // KEY_LEFT            = 263,      // Key: Cursor left
  // KEY_DOWN            = 264,      // Key: Cursor down
  // KEY_UP              = 265,      // Key: Cursor up
  if (reached_floor == true) {
    return true;
  } else {
    if (key == KEY_DOWN) {
      piece->block[0].y += (BLOCK_SIZE * 2 * speed);
      piece->block[1].y += (BLOCK_SIZE * 2 * speed);
      piece->block[2].y += (BLOCK_SIZE * 2 * speed);
      piece->block[3].y += (BLOCK_SIZE * 2 * speed);
    } else {
      piece->block[0].y += (BLOCK_SIZE * speed);
      piece->block[1].y += (BLOCK_SIZE * speed);
      piece->block[2].y += (BLOCK_SIZE * speed);
      piece->block[3].y += (BLOCK_SIZE * speed);
    }
  }

  // move piece to the left logic
  if (key == KEY_LEFT) {
    if (!reached_left_border) {
      // move piece to the left
      piece->block[0].x -= (BLOCK_SIZE * speed);
      piece->block[1].x -= (BLOCK_SIZE * speed);
      piece->block[2].x -= (BLOCK_SIZE * speed);
      piece->block[3].x -= (BLOCK_SIZE * speed);
    }
  } // move piece to the right logic
  if (key == KEY_RIGHT) {
    if (!reached_right_border) {
      piece->block[0].x += (BLOCK_SIZE * speed);
      piece->block[1].x += (BLOCK_SIZE * speed);
      piece->block[2].x += (BLOCK_SIZE * speed);
      piece->block[3].x += (BLOCK_SIZE * speed);
    }
  }
  return false;
}

void draw_piece(piece_t *piece) {
  for (int i = 0; i < 4; i++) {
    DrawRectangleRec(piece->block[i], piece->p_color);
  }
}

void free_All_pieces(All_Recs_t *all_pieces) {
  for (size_t i = 0; i < all_pieces->cap; i++) {
    free(all_pieces->all[i]);
  }
  free(all_pieces->all);
  free(all_pieces);
}
