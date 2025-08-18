#ifndef BLOCKS_H
#define BLOCKS_H

#include "raylib.h"
#include <stddef.h>

#define BLOCK_SIZE 10
#define EPSILON 0.01

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

typedef struct Rec_with_color {
  Color color;
  Rectangle rec;
} Rec_with_color_t;

typedef struct All_Recs {
  size_t len;
  size_t cap;
  Rec_with_color_t **all;
} All_Recs_t;

typedef struct ScoreBord {
  const char *text;
  char *score;
  Color area_color;
  Vector2 score_upper_left_pt;
  Vector2 score_upper_right_pt;
  Vector2 score_down_left_pt;
  Vector2 score_down_right_pt;
} ScoreBord_t;

All_Recs_t *allocAllPieces(void);
void free_All_pieces(All_Recs_t *all_pieces);
void create_piece(piece_t *piece);
void draw_piece(piece_t *piece);
ScoreBord_t *creat_score(void);
void draw_score(ScoreBord_t *score);
void free_score(ScoreBord_t *scor);

bool update_piece_pos(piece_t *piece, KeyboardKey key, float speed);

#endif
