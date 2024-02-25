#pragma once

#include <unordered_map>
#include <raylib.h>

namespace tetrispp {

inline constexpr int SQUARE_SIZE = 20;
inline constexpr int GRID_HEIGHT = 30;
inline constexpr int GRID_WIDTH  = 15;

struct Pos {
  size_t x;
  size_t y;

  Pos(const size_t x_, const size_t y_) : x{x_}, y{y_} {}
};

enum class Tetromino {
  O = 0,
  I,
  T,
  L,
  Z,
  S,
  None,
};

inline std::unordered_map<Tetromino, Color> colors{{Tetromino::O, YELLOW},  {Tetromino::I, BLUE},
                                                   {Tetromino::T, GREEN},   {Tetromino::L, ORANGE},
                                                   {Tetromino::Z, PURPLE},  {Tetromino::S, WHITE},
                                                   {Tetromino::None, BLACK}};

enum class Direction { Right, Left, Up, Down };

struct FallingTetrominoData {
  Tetromino type;
  Direction d;
  Pos pos;
  Tetromino next;
  Direction next_d;
};

}  // namespace tetrispp
