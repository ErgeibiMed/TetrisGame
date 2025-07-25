

#include "blocks.h"
#include <raylib.h>
#include <stddef.h>

void draw_piece(piece_t *piece, Vector2 *pos_block_1, Vector2 size) {
  switch (piece->piece_name) {
  case T:
    if (piece->hide == 1) {
      draw_piece_T(piece, pos_block_1, size);
    }
    break;
  case Square:
    if (piece->hide == 1) {
      draw_piece_Square(piece, pos_block_1, size);
    }
    break;
  case Stick:
    if (piece->hide == 1) {
      draw_piece_Stick(piece, pos_block_1, size);
    }
    break;
  case L_left:
    if (piece->hide == 1) {
      draw_piece_L_left(piece, pos_block_1, size);
    }
    break;
  case L_right:
    if (piece->hide == 1) {
      draw_piece_L_right(piece, pos_block_1, size);
    }
    break;
  case Dog_left:
    if (piece->hide == 1) {
      draw_piece_Dog_left(piece, pos_block_1, size);
    }
    break;
  case Dog_right:
    if (piece->hide == 1) {
      draw_piece_Dog_right(piece, pos_block_1, size);
    }
    break;
  default:
    break;
  }
}

void draw_piece_T(piece_t *piece, Vector2 *pos_block_1, Vector2 size) {
  piece->block[0] = *pos_block_1;
  // block[1] is under block[0]
  piece->block[1].x = piece->block[0].x;
  piece->block[1].y = piece->block[0].y + BLOCK_SIZE;
  // block[2] is on the left of block[1]
  piece->block[2].x = piece->block[1].x - BLOCK_SIZE;
  piece->block[2].y = piece->block[1].y;
  // block[3] is on the right of block[1]
  piece->block[3].x = piece->block[1].x + BLOCK_SIZE;
  piece->block[3].y = piece->block[1].y;
  piece->p_color = RED;
  for (int i = 0; i < 4; i++) {
    DrawRectangleV(piece->block[i], size, piece->p_color);
  }
}
void draw_piece_Square(piece_t *piece, Vector2 *pos_block_1, Vector2 size) {
  piece->block[0] = *pos_block_1;
  // block[1] is under block[0]
  piece->block[1].x = piece->block[0].x;
  piece->block[1].y = piece->block[0].y + BLOCK_SIZE;
  // block[2] is on the left of block[1]
  piece->block[2].x = piece->block[1].x - BLOCK_SIZE;
  piece->block[2].y = piece->block[1].y;
  // block[3] is on top of block[2]
  piece->block[3].x = piece->block[2].x;
  piece->block[3].y = piece->block[2].y - BLOCK_SIZE;
  piece->p_color = RED;
  for (int i = 0; i < 4; i++) {
    DrawRectangleV(piece->block[i], size, piece->p_color);
  }
}
void draw_piece_Stick(piece_t *piece, Vector2 *pos_block_1, Vector2 size) {
  piece->block[0] = *pos_block_1;
  // block[1] is under block[0]
  piece->block[1].x = piece->block[0].x;
  piece->block[1].y = piece->block[0].y + BLOCK_SIZE;
  // block[2] is under block[1]
  piece->block[2].x = piece->block[1].x;
  piece->block[2].y = piece->block[1].y + BLOCK_SIZE;
  // block[3] is under block[2]
  piece->block[3].x = piece->block[2].x;
  piece->block[3].y = piece->block[2].y + BLOCK_SIZE;
  piece->p_color = RED;
  for (int i = 0; i < 4; i++) {
    DrawRectangleV(piece->block[i], size, piece->p_color);
  }
}
void draw_piece_L_left(piece_t *piece, Vector2 *pos_block_1, Vector2 size) {
  piece->block[0] = *pos_block_1;
  // block[1] is under block[0]
  piece->block[1].x = piece->block[0].x;
  piece->block[1].y = piece->block[0].y + BLOCK_SIZE;
  // block[2] is under block[1]
  piece->block[2].x = piece->block[1].x;
  piece->block[2].y = piece->block[1].y + BLOCK_SIZE;
  // block[3] is on the left of block[2]
  piece->block[3].x = piece->block[2].x - BLOCK_SIZE;
  piece->block[3].y = piece->block[2].y;
  piece->p_color = RED;
  for (int i = 0; i < 4; i++) {
    DrawRectangleV(piece->block[i], size, piece->p_color);
  }
}

void draw_piece_L_right(piece_t *piece, Vector2 *pos_block_1, Vector2 size) {
  piece->block[0] = *pos_block_1;
  // block[1] is under block[0]
  piece->block[1].x = piece->block[0].x;
  piece->block[1].y = piece->block[0].y + BLOCK_SIZE;
  // block[2] is under block[1]
  piece->block[2].x = piece->block[1].x;
  piece->block[2].y = piece->block[1].y + BLOCK_SIZE;
  // block[3] is on the right of block[2]
  piece->block[3].x = piece->block[2].x + BLOCK_SIZE;
  piece->block[3].y = piece->block[2].y;
  piece->p_color = RED;
  for (int i = 0; i < 4; i++) {
    DrawRectangleV(piece->block[i], size, piece->p_color);
  }
}
void draw_piece_Dog_left(piece_t *piece, Vector2 *pos_block_1, Vector2 size) {
  piece->block[0] = *pos_block_1;
  // block[1] is on the left block[0]
  piece->block[1].x = piece->block[0].x - BLOCK_SIZE;
  piece->block[1].y = piece->block[0].y;
  // block[2] is under block[0]
  piece->block[2].x = piece->block[0].x;
  piece->block[2].y = piece->block[0].y + BLOCK_SIZE;
  // block[3] is on the right of block[2]
  piece->block[3].x = piece->block[2].x + BLOCK_SIZE;
  piece->block[3].y = piece->block[2].y;
  piece->p_color = RED;
  for (int i = 0; i < 4; i++) {
    DrawRectangleV(piece->block[i], size, piece->p_color);
  }
}
void draw_piece_Dog_right(piece_t *piece, Vector2 *pos_block_1, Vector2 size) {
  piece->block[0] = *pos_block_1;
  // block[1] is on the right of block[0]
  piece->block[1].x = piece->block[0].x + BLOCK_SIZE;
  piece->block[1].y = piece->block[0].y;
  // block[2] is under block[0]
  piece->block[2].x = piece->block[0].x;
  piece->block[2].y = piece->block[0].y + BLOCK_SIZE;
  // block[3] is on the left of block[2]
  piece->block[3].x = piece->block[2].x - BLOCK_SIZE;
  piece->block[3].y = piece->block[2].y;
  piece->p_color = RED;
  for (int i = 0; i < 4; i++) {
    DrawRectangleV(piece->block[i], size, piece->p_color);
  }
}

void move_piece_left(piece_t *piece) {
  switch (piece->piece_name) {
  case T: {
    bool border_left = piece->block[2].x > (BLOCK_SIZE * 0.05);
    if (border_left) {
      piece->block[0].x -= BLOCK_SIZE;
    }
  } break;
  case Stick: {
    bool border_left = piece->block[0].x > (BLOCK_SIZE * 0.05);
    if (border_left) {
      piece->block[0].x -= BLOCK_SIZE;
    }
  } break;
  case Square: {
    bool border_left = piece->block[2].x > (BLOCK_SIZE * 0.05);
    if (border_left) {
      piece->block[0].x -= BLOCK_SIZE;
    }
  } break;
  case L_left: {
    bool border_left = piece->block[3].x > (BLOCK_SIZE * 0.05);
    if (border_left) {
      piece->block[0].x -= BLOCK_SIZE;
    }
  } break;
  case L_right: {
    bool border_left = piece->block[2].x > (BLOCK_SIZE * 0.05);
    if (border_left) {
      piece->block[0].x -= BLOCK_SIZE;
    }
  } break;
  case Dog_left: {
    bool border_left = piece->block[1].x > (BLOCK_SIZE * 0.05);
    if (border_left) {
      piece->block[0].x -= BLOCK_SIZE;
    }
  } break;
  case Dog_right: {
    bool border_left = piece->block[3].x > (BLOCK_SIZE * 0.05);
    if (border_left) {
      piece->block[0].x -= BLOCK_SIZE;
    }
  } break;
  }
}
void move_piece_right(piece_t *piece) {
  switch (piece->piece_name) {
  case T: {
    bool border_right =
        piece->block[3].x < (GetScreenWidth() - (BLOCK_SIZE * 0.05));
    if (border_right) {
      piece->block[0].x += BLOCK_SIZE;
    }
  } break;
  case Stick: {
    bool border_right =
        piece->block[0].x < (GetScreenWidth() - (BLOCK_SIZE * 0.05));
    if (border_right) {
      piece->block[0].x += BLOCK_SIZE;
    }
  } break;
  case Square: {
    bool border_right =
        piece->block[1].x < (GetScreenWidth() - (BLOCK_SIZE * 0.05));
    if (border_right) {
      piece->block[0].x += BLOCK_SIZE;
    }
  } break;
  case L_left: {
    bool border_right =
        piece->block[2].x < (GetScreenWidth() - (BLOCK_SIZE * 0.05));
    if (border_right) {
      piece->block[0].x += BLOCK_SIZE;
    }
  } break;
  case L_right: {
    bool border_right =
        piece->block[3].x < (GetScreenWidth() - (BLOCK_SIZE * 0.05));
    if (border_right) {
      piece->block[0].x += BLOCK_SIZE;
    }
  } break;
  case Dog_left: {
    bool border_right =
        piece->block[3].x < (GetScreenWidth() - (BLOCK_SIZE * 0.05));
    if (border_right) {
      piece->block[0].x += BLOCK_SIZE;
    }
  } break;
  case Dog_right: {
    bool border_right =
        piece->block[1].x < (GetScreenWidth() - (BLOCK_SIZE * 0.05));
    if (border_right) {
      piece->block[0].x += BLOCK_SIZE;
    }
  } break;
  }
}
void move_piece_down(piece_t *piece) {}
