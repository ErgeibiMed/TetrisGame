#ifndef BLOCKS_H
#define BLOCKS_H

#include <raylib.h>

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
} piece_name_t;

typedef struct Piece {
  int hide;
  Vector2 block[4];
  piece_name_t piece_name;
  Color p_color;
} piece_t;

void move_piece_left(piece_t *piece);
void move_piece_right(piece_t *piece);
void move_piece_down(piece_t *piece);

void draw_piece(piece_t *piece, Vector2 *pos_block_1, Vector2 size);

void draw_piece_T(piece_t *piece, Vector2 *pos_block_1, Vector2 size);
void draw_piece_Square(piece_t *piece, Vector2 *pos_block_1, Vector2 size);
void draw_piece_Stick(piece_t *piece, Vector2 *pos_block_1, Vector2 size);
void draw_piece_L_left(piece_t *piece, Vector2 *pos_block_1, Vector2 size);
void draw_piece_L_right(piece_t *piece, Vector2 *pos_block_1, Vector2 size);
void draw_piece_Dog_left(piece_t *piece, Vector2 *pos_block_1, Vector2 size);
void draw_piece_Dog_right(piece_t *piece, Vector2 *pos_block_1, Vector2 size);

#endif
