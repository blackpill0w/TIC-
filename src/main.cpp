#include <fmt/core.h>
#include <raylib.h>

#include "./tetris.hpp"

int main() {
  InitWindow(
      tetrispp::GRID_WIDTH * tetrispp::SQUARE_SIZE, tetrispp::GRID_HEIGHT * tetrispp::SQUARE_SIZE,
      "TICpp"
  );

  Image icon_img = LoadImage("../icon.png");
  SetWindowIcon(icon_img);
  SetTargetFPS(60);

  tetrispp::TetrisGrid grid{};
  tetrispp::init_grid(grid);
  // fmt::println("Grid {}, {}", grid.size(), grid[0].size());

  tetrispp::put_tetromino_at(grid, tetrispp::Tetromino::O, tetrispp::Direction::Right, 0, 0);
  tetrispp::put_tetromino_at(grid, tetrispp::Tetromino::S, tetrispp::Direction::Left, 5, 5);

  print_grid(grid);

  while (not WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    tetrispp::draw_grid(grid);

    EndDrawing();
  }
  UnloadImage(icon_img);
  CloseWindow();
}
