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
  Color temp;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (IsKeyPressed(KEY_G)) {
      printf("KEY_G Pressed: application is shutting down\n");
      break;
    }
    if (piece == NULL) {
      piece = create_piece();
      temp = piece->p_color;
    }
    if (piece != NULL) {
      bool reached_floor = false;
      draw_piece(piece);
      /// Fix me
      switch (piece->piece_name) {
      case T:
      case Square:
        reached_floor = (piece->block[1].y) == (GetScreenHeight() - BLOCK_SIZE);
        break;
      case Stick:
        reached_floor = (piece->block[3].y) == (GetScreenHeight() - BLOCK_SIZE);
        break;
      case L_left:
      case L_right:
        reached_floor = (piece->block[0].y) == (GetScreenHeight() - BLOCK_SIZE);
        break;
      case Dog_left:
      case Dog_right:
        reached_floor = (piece->block[2].y) == (GetScreenHeight() - BLOCK_SIZE);
        break;
      }
      ///
      if (reached_floor) {
        for (size_t i = all_recs->len; i < all_recs->len + 4; i++) {
          *(all_recs->all[i]) = piece->block[i - all_recs->len];
        }
        all_recs->len += 4; // each pice is consiting of four rectangles
        piece = NULL;
      } else {
        // update piece pos
        piece->block[0].y += BLOCK_SIZE; //* GetFPS();
        piece->block[1].y += BLOCK_SIZE; //* GetFPS();
        piece->block[2].y += BLOCK_SIZE; //* GetFPS();
        piece->block[3].y += BLOCK_SIZE; //* GetFPS();
        if (IsKeyPressed(KEY_H)) {
          // move piece to the left
          piece->block[0].x -= BLOCK_SIZE; //* GetFPS();
          piece->block[1].x -= BLOCK_SIZE; //* GetFPS();
          piece->block[2].x -= BLOCK_SIZE; //* GetFPS();
          piece->block[3].x -= BLOCK_SIZE; //* GetFPS();
        }
        if (IsKeyPressed(KEY_L)) {
          // move piece to the right
          piece->block[0].x += BLOCK_SIZE; //* GetFPS();
          piece->block[1].x += BLOCK_SIZE; //* GetFPS();
          piece->block[2].x += BLOCK_SIZE; //* GetFPS();
          piece->block[3].x += BLOCK_SIZE; //* GetFPS();
        }
      }
    }
    if (all_recs->len > 0) {
      for (size_t k = 0; k < all_recs->len; k++) {
        Rectangle rec = *(all_recs->all[k]);
        DrawRectangleRec(rec, temp);
      }
    }
    EndDrawing();
  }

  free_All_pieces(all_recs);

  // CloseWindow();
  return 0;
}
