
#ifndef BORDERLOGIC_H
#define BORDERLOGIC_H

#include "TetrisLogic.h"
#include "raylib.h"
#include <stddef.h>

#define Preview_Window_SIZE (9 * BLOCK_SIZE)

typedef struct ScoreBord {
  const char *text;
  char *score;
  Color area_color;
  Vector2 score_upper_left_pt;
  Vector2 score_upper_right_pt;
  Vector2 score_down_left_pt;
  Vector2 score_down_right_pt;
} ScoreBord_t;

typedef struct PiecePreviewer {
  const char *text;
  Color area_color;
  Vector2 prvw_upper_left_pt;
  Vector2 prvw_upper_right_pt;
  Vector2 prvw_down_left_pt;
  Vector2 prvw_down_right_pt;
  piece_t piece;
} PiecePreviewer_t;

typedef struct Border {
  Color border_color;
  Vector2 border_upper_left_pt;
  Vector2 border_upper_right_pt;
  Vector2 border_down_left_pt;
  Vector2 border_down_right_pt;

} Border_t;

Border_t *create_border(void);
void draw_border(Border_t *border);
void free_border(Border_t *border);

ScoreBord_t *creat_score(void);
void draw_score(ScoreBord_t *score);
void free_score(ScoreBord_t *scor);
//
PiecePreviewer_t *create_preview(void);
void draw_preview(PiecePreviewer_t *preview);
void free_preview(PiecePreviewer_t *preview);
//

#endif
