#include "BorderLogic.h"
#include "TetrisLogic.h"
#include "raylib.h"
#include <stdlib.h>

#define Preview_Window_SIZE (9 * BLOCK_SIZE)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////:
/// PiecePreviewer
PiecePreviewer_t *create_preview(void) {
  //
  PiecePreviewer_t *p_prvw = malloc(sizeof(PiecePreviewer_t));
  p_prvw->text = "Next PIECE";
  p_prvw->area_color = MAROON;
  //
  p_prvw->prvw_upper_right_pt.x = 0.96 * GetScreenWidth();
  p_prvw->prvw_upper_right_pt.y = 0.20 * GetScreenHeight();
  //
  p_prvw->prvw_upper_left_pt.x =
      p_prvw->prvw_upper_right_pt.x - Preview_Window_SIZE;
  p_prvw->prvw_upper_left_pt.y = p_prvw->prvw_upper_right_pt.y;
  //
  p_prvw->prvw_down_right_pt.x = p_prvw->prvw_upper_right_pt.x;
  p_prvw->prvw_down_right_pt.y =
      p_prvw->prvw_upper_right_pt.y + Preview_Window_SIZE;
  //
  p_prvw->prvw_down_left_pt.x = p_prvw->prvw_upper_left_pt.x;
  p_prvw->prvw_down_left_pt.y =
      p_prvw->prvw_upper_left_pt.y + Preview_Window_SIZE;
  p_prvw->piece = create_piece(true);
  return p_prvw;
}
void draw_preview(PiecePreviewer_t *preview) {
  Vector2 text_pos = {
      .x = preview->prvw_upper_left_pt.x + 1.5 * BLOCK_SIZE,
      .y =
          (preview->prvw_upper_left_pt.y + preview->prvw_down_left_pt.y) * 0.5 -
          3.0 * BLOCK_SIZE};

  DrawText(preview->text, text_pos.x, text_pos.y, 5, WHITE);
  //////
  ///////
  ///

  float thick = 5.0;
  DrawLineEx(preview->prvw_upper_left_pt, preview->prvw_upper_right_pt, thick,
             preview->area_color);
  DrawLineEx(preview->prvw_down_left_pt, preview->prvw_down_right_pt, thick,
             preview->area_color);
  DrawLineEx(preview->prvw_upper_right_pt, preview->prvw_down_right_pt, thick,
             preview->area_color);

  DrawLineEx(preview->prvw_upper_left_pt, preview->prvw_down_left_pt, thick,
             preview->area_color);
  draw_piece(&preview->piece);
}
void free_preview(PiecePreviewer_t *preview) { free(preview); }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// SCORE BORD STUFF
ScoreBord_t *creat_score(void) {
  ScoreBord_t *score = malloc(sizeof(ScoreBord_t));
  if (score != NULL) {
    score->text = "SCORE";
    score->score = "000000";
    score->area_color = GRAY;
    //
    score->score_upper_right_pt.x = 0.96 * GetScreenWidth();
    score->score_upper_right_pt.y = 0.650 * GetScreenHeight();
    //
    score->score_upper_left_pt.x =
        score->score_upper_right_pt.x - Preview_Window_SIZE;
    score->score_upper_left_pt.y = score->score_upper_right_pt.y;
    //
    score->score_down_right_pt.x = score->score_upper_right_pt.x;
    score->score_down_right_pt.y =
        score->score_upper_right_pt.y + Preview_Window_SIZE;
    //
    score->score_down_left_pt.x = score->score_upper_left_pt.x;
    score->score_down_left_pt.y =
        score->score_upper_left_pt.y + Preview_Window_SIZE;
  }
  return score;
}
void draw_score(ScoreBord_t *score) {
  Vector2 text_pos = {
      .x = score->score_upper_left_pt.x + 3 * BLOCK_SIZE,
      .y = (score->score_upper_left_pt.y + score->score_down_left_pt.y) * 0.5 -
           2.0 * BLOCK_SIZE};

  DrawText(score->text, text_pos.x, text_pos.y, 5, WHITE);
  //////
  Vector2 score_pos = {.x = text_pos.x, .y = text_pos.y + 3 * BLOCK_SIZE};
  DrawText(score->score, score_pos.x, score_pos.y, 5, WHITE);
  ///////
  float thick = 5.0;
  DrawLineEx(score->score_upper_left_pt, score->score_upper_right_pt, thick,
             score->area_color);
  DrawLineEx(score->score_down_left_pt, score->score_down_right_pt, thick,
             score->area_color);
  DrawLineEx(score->score_upper_right_pt, score->score_down_right_pt, thick,
             score->area_color);

  DrawLineEx(score->score_upper_left_pt, score->score_down_left_pt, thick,
             score->area_color);
}
void free_score(ScoreBord_t *score) { free(score); }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Border_t *create_border(void) {
  Border_t *border = malloc(sizeof(Border_t));

  border->border_color = LIGHTGRAY;
  //
  border->border_upper_right_pt.x =
      0.96 * GetScreenWidth() - Preview_Window_SIZE - 2 * BLOCK_SIZE;
  border->border_upper_right_pt.y = 0.0;
  //
  border->border_upper_left_pt.x = 0.0;
  border->border_upper_left_pt.y = 0.0;
  //
  border->border_down_right_pt.x =
      0.96 * GetScreenWidth() - Preview_Window_SIZE - 2 * BLOCK_SIZE;
  border->border_down_right_pt.y = GetScreenHeight();
  //
  border->border_down_left_pt.x = 0.0;
  border->border_down_left_pt.y = GetScreenHeight();
  return border;
}
void draw_border(Border_t *border) {

  float thick = 10.0;
  DrawLineEx(border->border_down_left_pt, border->border_down_right_pt, thick,
             border->border_color);
  DrawLineEx(border->border_upper_right_pt, border->border_down_right_pt, thick,
             border->border_color);

  DrawLineEx(border->border_upper_left_pt, border->border_down_left_pt, thick,
             border->border_color);
}
void free_border(Border_t *border) { free(border); }
