#include "blocks.h"
#include <raylib.h>
#include <stdio.h>

#define SCREEN_WIDTH 500
#define SCREEN_HIGHT 500

int main(void) {

  // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HIGHT, "TETRIS GAME");
  Vector2 border_right_up = {.x = GetScreenWidth() * 0.75, .y = 0.0};
  Vector2 border_right_down = {.x = GetScreenWidth() * 0.75,
                               .y = SCREEN_HIGHT * 1.0};
  Vector2 posObj = {.x = GetScreenWidth() / 2.0, .y = 0};
  piece_t piece[7] = {0};

  Vector2 size = {.x = BLOCK_SIZE, .y = BLOCK_SIZE};
  int i = 0;
  piece[0].piece_name = T;
  piece[0].hide = 1;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (IsKeyPressed(KEY_G)) {
      printf("KEY_G Pressed: application is shutting down\n");
      break;
    }
    DrawLineEx(border_right_up, border_right_down, 3.5, GREEN);
    // if (posObj.y >= GetScreenHeight()) {
    //   posObj.y = 0.0;
    // }
    if (posObj.y >= (GetScreenHeight() - (4.0 * BLOCK_SIZE))) {
      piece[i].hide = 0;
      i++;
      if (i > 6) {
        i = 0;
      }
      piece[i].piece_name = i;

      piece[i].hide = 1;
      posObj.y = 0.0;
    }
    draw_piece(&piece[i], &posObj, size);
    posObj.y += 10.0 * (GetFrameTime() * 5.00);
    if (IsKeyPressed(KEY_LEFT)) {
      move_piece_left(&piece[i]);
      posObj.x = piece[i].block[0].x;
    }
    if (IsKeyPressed(KEY_RIGHT)) {
      move_piece_right(&piece[i]);
      posObj.x = piece[i].block[0].x;
    }
    if (IsKeyPressed(KEY_DOWN)) {
      move_piece_down(&piece[i]);
      posObj.x = piece[i].block[0].x;
    }

    EndDrawing();
  }

  return 0;
}
