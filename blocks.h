#ifndef BLOCKS_H
#define BLOCKS_H

#include "raylib.h"
#include <stddef.h>

#define BLOCK_SIZE 10
/* raylib api only provide a function
 * to draw rectangles
 * but all pieces consiste of squares(ie:block)
 * REC_SIZE is just a way to represent the block size
 */
typedef enum piece_name {
  T,
  Square,
  Stick,
  L_left,
  L_right,
  Dog_left,
  Dog_right,
} piece_name;

typedef enum Direction {
  DOWN,
  UP,
  LEFT,
  RIGHT,
} Direction;

typedef struct Piece {
  piece_name piece_name;
  Direction dir;
  bool active;
  Color p_color;
  Rectangle block[4];
} piece_t;

typedef struct All_Recs {
  size_t len;
  size_t cap;
  Rectangle **all;
} All_Recs_t;

All_Recs_t *allocAllPieces(void);
void free_All_pieces(All_Recs_t *all_pieces);
piece_t *create_piece(void);
void draw_piece(piece_t *piece);

void move_piece_left(piece_t *piece);
void move_piece_right(piece_t *piece);
void update_piece_pos(piece_t *piece, float speed);

#endif
