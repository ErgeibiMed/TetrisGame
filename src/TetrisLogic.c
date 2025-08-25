#include "TetrisCommon.h"
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
//////
piece_t create_piece_at_pos(Vector2 initial_pos, piece_name p_n) {
  // Vector2 initial_pos;
  ////  if (for_prvw == true) {
  ////    float x = 0.95 * GetScreenWidth() - Preview_Window_SIZE + 4 *
  ////    BLOCK_SIZE; float y = 0.20 * GetScreenWidth() + 3 * BLOCK_SIZE;
  ////    initial_pos = (Vector2){x, y};
  ////  } else {
  // initial_pos = (Vector2){.x = GetScreenWidth() / 2.0, .y = 0.0};
  piece_t piece;
  piece.piece_name = p_n;
  piece.block[0].x = initial_pos.x;
  piece.block[0].y = initial_pos.y;
  switch (p_n) {
  case T:
    piece.dir = UP;
    // block[1] is under block[0]
    piece.block[1].x = piece.block[0].x;
    piece.block[1].y = piece.block[0].y + BLOCK_SIZE;

    // block[2] is on the left of block[1]
    piece.block[2].x = piece.block[1].x - BLOCK_SIZE;
    piece.block[2].y = piece.block[1].y;
    // block[3] is on the right of block[1]
    piece.block[3].x = piece.block[1].x + BLOCK_SIZE;
    piece.block[3].y = piece.block[1].y;
    // each pice has a color
    piece.p_color = RED;
    break;
  case Square:
    piece.dir = UP;
    // block[1] is under block[0]
    piece.block[1].x = piece.block[0].x;
    piece.block[1].y = piece.block[0].y + BLOCK_SIZE;
    // block[2] is on the left of block[1]
    piece.block[2].x = piece.block[1].x - BLOCK_SIZE;
    piece.block[2].y = piece.block[1].y;
    // block[3] is on top of block[2]
    piece.block[3].x = piece.block[2].x;
    piece.block[3].y = piece.block[2].y - BLOCK_SIZE;
    // each pice has a color
    piece.p_color = GREEN;
    break;
  case Stick:
    piece.dir = UP;
    // block[1] is under block[0]
    piece.block[1].x = piece.block[0].x;
    piece.block[1].y = piece.block[0].y + BLOCK_SIZE;
    // block[2] is under block[1]
    piece.block[2].x = piece.block[1].x;
    piece.block[2].y = piece.block[1].y + BLOCK_SIZE;
    // block[3] is under block[2]
    piece.block[3].x = piece.block[2].x;
    piece.block[3].y = piece.block[2].y + BLOCK_SIZE;
    // each pice has a color
    piece.p_color = BLUE;
    break;
  case L_left:
    piece.dir = LEFT;
    // block[1] is under of block[0]
    piece.block[1].x = piece.block[0].x;
    piece.block[1].y = piece.block[0].y + BLOCK_SIZE;
    // block[2] is under of block[1]
    piece.block[2].x = piece.block[1].x;
    piece.block[2].y = piece.block[1].y + BLOCK_SIZE;
    // block[3] is on the left of block[2]
    piece.block[3].x = piece.block[2].x - BLOCK_SIZE;
    piece.block[3].y = piece.block[2].y;
    // each pice has a color
    piece.p_color = YELLOW;
    break;
  case L_right:
    piece.dir = RIGHT;
    // block[1] is under block[0]
    piece.block[1].x = piece.block[0].x;
    piece.block[1].y = piece.block[0].y + BLOCK_SIZE;
    // block[2] is under of block[1]
    piece.block[2].x = piece.block[1].x;
    piece.block[2].y = piece.block[1].y + BLOCK_SIZE;
    // block[3] is on top of block[2]
    piece.block[3].x = piece.block[2].x + BLOCK_SIZE;
    piece.block[3].y = piece.block[2].y;
    // each pice has a color
    piece.p_color = ORANGE;
    break;
  case Dog_left:
    piece.dir = LEFT;
    // block[1] is on the right of block[0]
    piece.block[1].x = piece.block[0].x + BLOCK_SIZE;
    piece.block[1].y = piece.block[0].y;
    // block[2] is under block[1]
    piece.block[2].x = piece.block[1].x;
    piece.block[2].y = piece.block[1].y + BLOCK_SIZE;
    // block[3] is on the right of block[2]
    piece.block[3].x = piece.block[2].x + BLOCK_SIZE;
    piece.block[3].y = piece.block[2].y;
    // each pice has a color
    piece.p_color = BLUE;
    break;
  case Dog_right:
    piece.dir = RIGHT;
    // block[1] is on the left of block[0]
    piece.block[1].x = piece.block[0].x - BLOCK_SIZE;
    piece.block[1].y = piece.block[0].y;
    // block[2] is under block[1]
    piece.block[2].x = piece.block[1].x;
    piece.block[2].y = piece.block[1].y + BLOCK_SIZE;
    // block[3] is on the left of block[2]
    piece.block[3].x = piece.block[2].x - BLOCK_SIZE;
    piece.block[3].y = piece.block[2].y;
    // each pice has a color
    piece.p_color = VIOLET;
    break;
  }
  // each has consist of 4 rectangle of size BLOCK_SIZE
  for (size_t i = 0; i < 4; i++) {
    piece.block[i].height = BLOCK_SIZE;
    piece.block[i].width = BLOCK_SIZE;
  }
  return piece;
}

size_t get_index_block_closest_to_floor(piece_t *piece) {

  float closest_to_floor = piece->block[0].y;
  size_t down = 0;

  for (size_t j = 0; j < 4; j++) {
    if (piece->block[j].y >= closest_to_floor) {
      down = j;
      closest_to_floor = piece->block[j].y;
    }
  }
  return down;
}

size_t get_index_block_closest_to_left_border(piece_t *piece) {

  size_t left = 0;
  float closest_to_left_border = piece->block[0].x;

  for (size_t j = 0; j < 4; j++) {

    if (piece->block[j].x <= closest_to_left_border) {
      closest_to_left_border = piece->block[j].x;
      left = j;
    }
  }
  return left;
}

size_t get_index_block_closest_to_right_border(piece_t *piece) {
  size_t right = 0;
  float closest_to_right_border = piece->block[0].x;
  for (size_t j = 0; j < 4; j++) {
    if (piece->block[j].x >= closest_to_right_border) {
      closest_to_right_border = piece->block[j].x;
      right = j;
    }
  }
  return right;
}

Collided_With
check_collision_with_border_or_another_piece(piece_t *piece, Border_t *border,
                                             All_Recs_t *All_recs) {

  size_t left = get_index_block_closest_to_left_border(piece);
  size_t right = get_index_block_closest_to_right_border(piece);
  size_t down = get_index_block_closest_to_floor(piece);
  if (CheckCollisionRecs(border->down_border, piece->block[down])) {
    return DOWN_BORDER;
  }
  if (CheckCollisionRecs(border->left_border, piece->block[left])) {
    return LEFT_BORDER;
  }
  if (CheckCollisionRecs(border->right_border, piece->block[right])) {
    return RIGHT_BORDER;
  }
  for (size_t i = 0; i < All_recs->len; i++) {
    if (CheckCollisionRecs(All_recs->all[i]->rec, piece->block[down]) ||
        CheckCollisionRecs(All_recs->all[i]->rec, piece->block[right]) ||
        CheckCollisionRecs(All_recs->all[i]->rec, piece->block[left])) {
      return ANOTHER_PIECE;
    }
  }

  return NOTHING;
}

bool update_piece_pos(piece_t *piece, KeyboardKey key, Border_t *border,
                      All_Recs_t *All_recs) {
  // update piece pos
  //
  // KEY_RIGHT           = 262,      // Key: Cursor right
  // KEY_LEFT            = 263,      // Key: Cursor left
  // KEY_DOWN            = 264,      // Key: Cursor down
  // KEY_UP              = 265,      // Key: Cursor up

  Collided_With collision_with_border_or_another_piece =
      check_collision_with_border_or_another_piece(piece, border, All_recs);
  float speed = GetFrameTime() * BLOCK_SIZE * 20;

  if (collision_with_border_or_another_piece == DOWN_BORDER) {
    return true;
  }

  if (collision_with_border_or_another_piece == ANOTHER_PIECE) {
    return true;
  }

  if (collision_with_border_or_another_piece != DOWN_BORDER) {
    piece->block[0].y += 0.5 * speed;
    piece->block[1].y += 0.5 * speed;
    piece->block[2].y += 0.5 * speed;
    piece->block[3].y += 0.5 * speed;
    if (key == KEY_DOWN) {
      piece->block[0].y += speed;
      piece->block[1].y += speed;
      piece->block[2].y += speed;
      piece->block[3].y += speed;
    }
  }
  if (key == KEY_LEFT) {
    // move piece to the left
    if (collision_with_border_or_another_piece != LEFT_BORDER) {
      piece->block[0].x -= speed;
      piece->block[1].x -= speed;
      piece->block[2].x -= speed;
      piece->block[3].x -= speed;
    }
  }
  // move piece to the right logic
  if (key == KEY_RIGHT) {
    if (collision_with_border_or_another_piece != RIGHT_BORDER) {
      piece->block[0].x += speed;
      piece->block[1].x += speed;
      piece->block[2].x += speed;
      piece->block[3].x += speed;
    }
  }
  return false;
}

void draw_piece(piece_t *piece) {
  for (int i = 0; i < 4; i++) {
    DrawRectangleRec(piece->block[i], piece->p_color);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void free_All_pieces(All_Recs_t *all_pieces) {
  for (size_t i = 0; i < all_pieces->cap; i++) {
    free(all_pieces->all[i]);
  }
  free(all_pieces->all);
  free(all_pieces);
}
