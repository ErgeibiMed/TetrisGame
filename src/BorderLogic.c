#include "TetrisCommon.h"
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
  Vector2 init_pos = {
      .x = p_prvw->prvw_upper_left_pt.x + Preview_Window_SIZE * 0.5,
      .y = p_prvw->prvw_upper_left_pt.y + Preview_Window_SIZE * 0.5};

  piece_name p_n = (rand() % 7); // THE number of pieces is 7
  p_prvw->piece = create_piece_at_pos(init_pos, p_n);
  return p_prvw;
}
void draw_preview(PiecePreviewer_t *preview) {
  Vector2 text_pos = {
      .x = preview->prvw_upper_left_pt.x + 1.5 * BLOCK_SIZE,
      .y =
          preview->prvw_upper_left_pt.y +
          (preview->prvw_down_left_pt.y - preview->prvw_upper_left_pt.y) * 0.5 -
          3.5 * BLOCK_SIZE};

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
ScoreBord_t *create_score(void) {
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

  border->left_border = (Rectangle){
      .x = 0.0, .y = 0.0, .width = BLOCK_SIZE, .height = GetScreenHeight()};
  border->right_border = (Rectangle){.x = 0.96 * GetScreenWidth() -
                                          Preview_Window_SIZE - 2 * BLOCK_SIZE,
                                     .y = 0.0,
                                     .width = BLOCK_SIZE,
                                     .height = GetScreenHeight()};

  border->down_border =
      (Rectangle){.x = BLOCK_SIZE,
                  .y = GetScreenHeight() - BLOCK_SIZE,
                  .width = 0.96 * GetScreenWidth() - Preview_Window_SIZE -
                           2 * BLOCK_SIZE - BLOCK_SIZE,
                  .height = BLOCK_SIZE};
  return border;
}
void draw_border(Border_t *border) {

  DrawRectangleRec(border->left_border, border->border_color);
  DrawRectangleRec(border->right_border, border->border_color);
  DrawRectangleRec(border->down_border, border->border_color);
}
void free_border(Border_t *border) { free(border); }
