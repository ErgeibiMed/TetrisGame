#include "BorderLogic.h"
#include "TetrisLogic.h"
#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define LEVEL 10

int main(void) {

  srand(time(NULL));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TETRIS GAME");
  //  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(60);
  All_Recs_t *all_recs = allocAllPieces();
  ScoreBord_t *score = creat_score();
  PiecePreviewer_t *Pice_prvw = create_preview();
  Border_t *border = create_border();
  piece_t *piece = NULL;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    //////////////////////:
    draw_score(score);
    draw_preview(Pice_prvw);
    draw_border(border);
    ///////////////////
    if (piece == NULL) {
      piece = malloc(sizeof(piece_t));
      bool for_preview = false;
      *piece = create_piece(for_preview);
    }
    if (piece != NULL) {
      draw_piece(piece);
      KeyboardKey key = GetKeyPressed();
      float speed = 0;
      if (IsKeyPressed(key)) {
        speed = BLOCK_SIZE;
      } else {
        speed = LEVEL * BLOCK_SIZE * GetFrameTime();
      }
      bool reached_floor = update_piece_pos(piece, key, speed);
      if (reached_floor == true) {
        for (size_t i = all_recs->len; i < all_recs->len + 4; i++) {
          all_recs->all[i]->rec = piece->block[i - all_recs->len];
          all_recs->all[i]->color = piece->p_color;
        }
        all_recs->len += 4; // each pice is consiting of four rectangles
        free(piece);
        piece = NULL;
      }
    }
    if (all_recs->len > 0) {
      for (size_t k = 0; k < all_recs->len; k++) {
        Rectangle rec = (all_recs->all[k]->rec);
        Color clr = (all_recs->all[k]->color);
        DrawRectangleRec(rec, clr);
      }
      if (IsKeyPressed(KEY_G)) {
        printf("KEY_G Pressed: application is shutting down\n");
        break;
      }
    }
    EndDrawing();
  }

  free(score);
  free_preview(Pice_prvw);
  free_border(border);
  free_All_pieces(all_recs);

  CloseWindow();
  return 0;
}
