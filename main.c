#include "blocks.h"
#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 500
#define SCREEN_HIGHT 500

int main(void) {

  // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HIGHT, "TETRIS GAME");
  SetTargetFPS(30);
  All_Recs_t *all_recs = allocAllPieces();
  piece_t *piece = NULL;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (IsKeyPressed(KEY_G)) {
      printf("KEY_G Pressed: application is shutting down\n");
      break;
    }
    if (piece == NULL) {
      piece = malloc(sizeof(piece_t));
      create_piece(piece);
    }
    if (piece != NULL) {
      draw_piece(piece);
      KeyboardKey key = GetKeyPressed();
      bool reached_floor = update_piece_pos(piece, key, 0.1);
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
    }
    EndDrawing();
  }

  free_All_pieces(all_recs);

  CloseWindow();
  return 0;
}
