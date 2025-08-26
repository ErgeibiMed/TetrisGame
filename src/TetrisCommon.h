#ifndef TETRISCOMMON_H
#define TETRISCOMMON_H

/*
****************** Pieces Logic ***********************************
*/

#include "raylib.h"
#include <stddef.h>
#define BLOCK_SIZE 10
#define EPSILON 0.01
#define Preview_Window_SIZE (9 * BLOCK_SIZE)

typedef enum {
  NOTHING,
  ANOTHER_PIECE,
  LEFT_BORDER,
  RIGHT_BORDER,
  DOWN_BORDER,
} Collided_With;

/* raylib api only provide a function
 * to draw rectangles
 * but all pieces consiste of squares(ie:block)
 * REC_SIZE is just a way to represent the block size
 */
typedef enum {
  T,
  Square,
  Stick,
  L_left,
  L_right,
  Dog_left,
  Dog_right,
} piece_name;

typedef enum {
  DOWN,
  UP,
  LEFT,
  RIGHT,
} Direction;
typedef struct Piece {
  piece_name piece_name;
  Direction dir;
  Color p_color;
  Rectangle block[4];
} piece_t;

typedef struct {
  Color color;
  Rectangle rec;
} Rec_with_color_t;

typedef struct {
  size_t len;
  size_t cap;
  Rec_with_color_t **all;
} All_Recs_t;

All_Recs_t *allocAllPieces(void);
void free_All_pieces(All_Recs_t *all_pieces);
piece_t create_piece_at_pos(Vector2 initial_pos, piece_name p_n);
void rotate_piece_UpToLeft(piece_t *piece);
void draw_piece(piece_t *piece);
///

/*
****************** Pieces Logic ***********************************
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/*
****************** Border Logic ***********************************
*/

#define Preview_Window_SIZE (9 * BLOCK_SIZE)

typedef struct {
  const char *text;
  char *score;
  Color area_color;
  Vector2 score_upper_left_pt;
  Vector2 score_upper_right_pt;
  Vector2 score_down_left_pt;
  Vector2 score_down_right_pt;
} ScoreBord_t;

typedef struct {
  const char *text;
  Color area_color;
  Vector2 prvw_upper_left_pt;
  Vector2 prvw_upper_right_pt;
  Vector2 prvw_down_left_pt;
  Vector2 prvw_down_right_pt;
  piece_t piece;
} PiecePreviewer_t;

typedef struct {
  Color border_color;
  Rectangle left_border;
  Rectangle right_border;
  Rectangle down_border;

} Border_t;

Border_t *create_border(void);
void draw_border(Border_t *border);
void free_border(Border_t *border);

ScoreBord_t *create_score(void);
void draw_score(ScoreBord_t *score);
void free_score(ScoreBord_t *scor);
//
PiecePreviewer_t *create_preview(void);
void update_preview(void);
void draw_preview(PiecePreviewer_t *preview);
void free_preview(PiecePreviewer_t *preview);
//

/*
****************** Border Logic ***********************************
*/
bool update_piece(piece_t *piece, KeyboardKey key, Border_t *Border,
                  All_Recs_t *All_recs);

///////////////////////////

#endif
