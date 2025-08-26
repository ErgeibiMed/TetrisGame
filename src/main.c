#include "TetrisCommon.h"
#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define LEVEL 1

int main(void) {

  srand(time(NULL));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TETRIS GAME");
  //  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(60);
  All_Recs_t *all_recs = allocAllPieces();
  ScoreBord_t *score = create_score();
  PiecePreviewer_t *Piece_prvw = create_preview();
  Border_t *border = create_border();
  piece_t *piece = NULL;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    //////////////////////:
    draw_score(score);
    draw_preview(Piece_prvw);
    draw_border(border);
    ///////////////////
    bool piece_isNot_freed = true;
    if (piece == NULL) {
      piece = malloc(sizeof(piece_t));
      Vector2 init_pos = {.x = GetScreenWidth() * 0.4, .y = 0};
      *piece = create_piece_at_pos(init_pos, Piece_prvw->piece.piece_name);
      piece_name p_n = (piece_name)(rand() % 7); // THE number of pieces is 7;
      ///////////////// ** UPDATE PREVIEW  **      ////////////////
      Vector2 init_pos_for_preview = {.x = Piece_prvw->piece.block[0].x,
                                      .y = Piece_prvw->piece.block[0].y};
      Piece_prvw->piece = create_piece_at_pos(init_pos_for_preview, p_n);
      ///////////////// ** UPDATE PREVIEW  **      ////////////////
    }
    if (piece != NULL) {
      draw_piece(piece);
      KeyboardKey key = GetKeyPressed();
      bool reached_floor = update_piece(piece, key, border, all_recs);
      if (reached_floor == true) {
        for (size_t i = all_recs->len; i < all_recs->len + 4; i++) {
          all_recs->all[i]->rec = piece->block[i - all_recs->len];
          all_recs->all[i]->color = piece->p_color;
        }
        all_recs->len += 4; // each pice is consiting of four rectangles
        free(piece);
        piece_isNot_freed = false;

        piece = NULL;
      }
    }
    if (all_recs->len > 0) {
      for (size_t k = 0; k < all_recs->len; k++) {
        Rectangle rec = (all_recs->all[k]->rec);
        Color clr = (all_recs->all[k]->color);
        DrawRectangleRec(rec, clr);
      }
    }
    if (IsKeyPressed(KEY_G)) {
      printf("KEY_G Pressed: application is shutting down\n");
      if (piece_isNot_freed == true) {
        free(piece);
      }
      break;
    }
    EndDrawing();
  }

  free(score);
  free_preview(Piece_prvw);
  free_border(border);
  free_All_pieces(all_recs);

  CloseWindow();
  return 0;
}
