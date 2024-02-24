#include <fmt/core.h>
#include <raylib.h>

#include "./tetris.hpp"

int main() {
  InitWindow(
      tetrispp::GRID_WIDTH * tetrispp::SQUARE_SIZE, tetrispp::GRID_HEIGHT * tetrispp::SQUARE_SIZE,
      "TICpp"
  );
  fmt::println(
      "Window {}, {}", tetrispp::GRID_WIDTH * tetrispp::SQUARE_SIZE,
      tetrispp::GRID_HEIGHT * tetrispp::SQUARE_SIZE
  );
  SetTargetFPS(60);

  tetrispp::TetrisGrid grid{};
  tetrispp::init_grid(grid);
  //fmt::println("Grid {}, {}", grid.size(), grid[0].size());

  std::array<tetrispp::Pos, 4> x = get_full_positions_of_tetromino(
      tetrispp::Tetromino::O, tetrispp::Direction::Right, grid[0].size() - 1, grid.size() - 1
  );
  for (auto &pos : x) {
    grid[pos.x][pos.y] = tetrispp::Tetromino::O;
  }
  x = get_full_positions_of_tetromino(
      tetrispp::Tetromino::T, tetrispp::Direction::Right, 5, 5
  );
  for (auto &pos : x) {
    grid[pos.x][pos.y] = tetrispp::Tetromino::T;
  }
  print_grid(grid);

  while (not WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    tetrispp::draw_grid(grid);

    EndDrawing();
  }

  CloseWindow();
}
