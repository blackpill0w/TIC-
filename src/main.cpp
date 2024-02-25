#include <fmt/core.h>
#include <raylib.h>

#include "./tetris.hpp"

using namespace tetrispp;

int main() {
  int fps = 60;

  InitWindow(200 + GRID_WIDTH * SQUARE_SIZE, GRID_HEIGHT * SQUARE_SIZE, "TICpp");

  Image icon_img = LoadImage("../icon.png");
  SetWindowIcon(icon_img);
  SetTargetFPS(fps);

  TetrisGrid grid{};
  init_grid(grid);

  FallingTetrominoData falling_t = new_falling_tetromino(grid);
  put_tetromino_at(grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y);
  fmt::println("{}", falling_tetromino_data_to_string(falling_t));

  bool lost = false;
  int blink = 0;

  while (not WindowShouldClose()) {
    if (IsKeyDown(KEY_F)) {
      SetTargetFPS(++fps);
      fmt::println("FPS: {}", fps);
    } else if (IsKeyDown(KEY_V)) {
      SetTargetFPS(--fps);
      fmt::println("FPS: {}", fps);
    }
    if (lost and IsKeyDown(KEY_R)) {
      lost = false;
      init_grid(grid);
      falling_t = new_falling_tetromino(grid, falling_t.next, falling_t.d);
      put_tetromino_at(grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y);
    } else if (not lost) {
      if (IsKeyDown(KEY_RIGHT) and
          can_move_tetromino_to(
              grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y, Direction::Right
          )) {
        clear_tetromino_at(grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y);
        ++falling_t.pos.x;
        put_tetromino_at(grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y);
      }
      else if (IsKeyDown(KEY_LEFT) and
        can_move_tetromino_to(
                                        grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y, Direction::Left
        )) {
        clear_tetromino_at(grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y);
        --falling_t.pos.x;
        put_tetromino_at(grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y);

      } else if (IsKeyDown(KEY_K)) {
        falling_t.next = Tetromino::I;
      }
    }
    if (not lost) {
      if (can_move_tetromino_to(
              grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y, Direction::Down
          )) {
        clear_tetromino_at(grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y);
        ++falling_t.pos.y;
        put_tetromino_at(grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y);
      } else {
        clear_full_lines(grid);
        falling_t = new_falling_tetromino(grid, falling_t.next, falling_t.next_d);
        if (can_put_tetromino_at(
                grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y
            )) {
          put_tetromino_at(grid, falling_t.type, falling_t.d, falling_t.pos.x, falling_t.pos.y);
        } else {
          lost = true;
          print_grid(grid);
        }
        fmt::println("{}", falling_tetromino_data_to_string(falling_t));
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(SQUARE_SIZE * GRID_WIDTH, 0, SQUARE_SIZE * GRID_WIDTH, GetRenderHeight(), WHITE);
    draw_grid(grid);
    draw_tetromino_at(falling_t.next, falling_t.next_d, SQUARE_SIZE * GRID_WIDTH + 80, 100);
    if (lost) {
      DrawText("You Lost!", 50, 200, 36, RED);
      DrawText("Press 'R' to play again.", 50, 240, 36, RED);
      if (blink > 5) {
        draw_tetromino_at(
            falling_t.type, falling_t.d, falling_t.pos.x * SQUARE_SIZE,
            falling_t.pos.y * SQUARE_SIZE, RED
        );
        --blink;
      } else {
        ++blink;
      }
    }

    EndDrawing();
  }
  UnloadImage(icon_img);
  CloseWindow();
}
