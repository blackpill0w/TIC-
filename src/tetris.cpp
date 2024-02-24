#include <array>
#include <raylib.h>
#include <fmt/core.h>

#include "./tetris.hpp"

namespace tetrispp {
void init_grid(TetrisGrid &grid) {
  grid.reserve(GRID_HEIGHT);
  for (unsigned l = 0; l < GRID_HEIGHT; ++l) {
    grid.emplace_back();
    grid[l].reserve(GRID_WIDTH);
    for (unsigned c = 0; c < GRID_WIDTH; ++c) {
      grid[l].push_back(Tetromino::None);
    }
  }
}

void print_grid(TetrisGrid &grid) {
  static std::unordered_map<Tetromino, char> tetromino_text{
      {Tetromino::O, 'O'}, {Tetromino::I, 'I'}, {Tetromino::T, 'T'},   {Tetromino::L, 'L'},
      {Tetromino::Z, 'Z'}, {Tetromino::S, 'S'}, {Tetromino::None, '.'}
  };
  for (auto &l : grid) {
    for (auto c : l) {
      fmt::print("{}, ", tetromino_text[c]);
    }
    fmt::println("");
  }
}

void draw_grid(TetrisGrid &grid, const int x_offset, const int y_offset) {
  int x = 0, y = 0;
  for (const auto &l : grid) {
    x = 0;
    for (const auto c : l) {
      if (c != Tetromino::None) {
        DrawRectangle(x + x_offset, y + y_offset, SQUARE_SIZE, SQUARE_SIZE, colors[c]);
      }
      x += SQUARE_SIZE;
    }
    y += SQUARE_SIZE;
  }
}

std::array<Pos, 4> get_full_positions_of_tetromino(
    const Tetromino t, const Direction d, const int x, const int y
) {
  using enum Direction;
  // Given a position of a tetromino and the direction it's facing, get all squares
  switch (t) {
    case Tetromino::O: return {Pos{x, y}, {x + 1, y}, {x, y + 1}, {x + 1, y + 1}};
    case Tetromino::I:
      switch (d) {
        case Right: [[fallthrough]];
        case Left: return {Pos{x, y}, {x, y + 1}, {x, y + 2}, {x, y + 3}};
        case Up: [[fallthrough]];
        case Down: return {Pos{x, y}, {x + 1, y}, {x + 2, y}, {x + 3, y}};
      }
      [[fallthrough]];
    case Tetromino::T:
      switch (d) {
        case Right: return {Pos{x, y}, {x, y + 1}, {x, y + 2}, {x + 1, y + 1}};
        case Left: return {Pos{x, y}, {x, y + 1}, {x, y + 2}, {x - 1, y + 1}};
        case Up: return {Pos{x, y}, {x, y + 1}, {x + 1, y + 1}, {x - 1, y + 1}};
        case Down: return {Pos{x, y}, {x + 1, y}, {x + 2, y}, {x + 1, y + 1}};
      }
      [[fallthrough]];
    case Tetromino::L:
      switch (d) {
        case Right: return {Pos{x, y}, {x, y + 1}, {x, y + 2}, {x + 1, y + 1}};
        case Left: return {Pos{x, y}, {x, y + 1}, {x + 1, y + 1}, {x + 1, y + 2}};
        case Up: return {Pos{x, y}, {x + 1, y}, {x + 2, y}, {x + 2, y - 1}};
        case Down: return {Pos{x, y}, {x, y + 1}, {x + 1, y}, {x + 2, y}};
      }
      [[fallthrough]];

    case Tetromino::Z:
      switch (d) {
        case Right: [[fallthrough]];
        case Left: return {Pos{x, y}, {x + 1, y}, {x + 1, y + 1}, {x + 2, y + 1}};
        case Up: [[fallthrough]];
        case Down: return {Pos{x, y}, {x, y + 1}, {x - 1, y + 1}, {x - 1, y + 2}};
      }
      [[fallthrough]];
    case Tetromino::S:
      switch (d) {
        case Right: [[fallthrough]];
        case Left: return {Pos{x, y}, {x + 1, y}, {x + 1, y - 1}, {x + 2, y - 1}};
        case Up: [[fallthrough]];
        case Down: return {Pos{x, y}, {x + 1, y}, {x + 1, y + 1}, {x + 1, y + 2}};
      }
      [[fallthrough]];
    default: return {Pos{x, y}, {x, y}, {x, y}, {x, y}};
  }
}

void put_tetromino_at(
    TetrisGrid &grid, const Tetromino t, const Direction d, const int x, const int y
);

void clear_tetromino_at(
    TetrisGrid &grid, const Tetromino t, const Direction d, const int x, const int y
);
}  // namespace tetrispp
