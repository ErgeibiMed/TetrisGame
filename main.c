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
  float Obj_size = 20;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (IsKeyPressed(KEY_G)) {
      printf("KEY_G Pressed: application is shutting down\n");
      break;
    }
    DrawLineEx(border_right_up, border_right_down, 3.5, GREEN);
    DrawCircleV(posObj, Obj_size, RED);
    if (posObj.y >= GetScreenHeight()) {
      posObj.y = 0.0;
    }
    posObj.y += 10.0 * (GetFrameTime() * 1.00);

    EndDrawing();
  }

  return 0;
}
