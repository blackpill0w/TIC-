#pragma once

#include <vector>
#include <unordered_map>
#include <raylib.h>

namespace tetrispp {

constexpr int SQUARE_SIZE = 20;
constexpr int GRID_HEIGHT = 30;
constexpr int GRID_WIDTH  = 15;

struct Pos {
  int x;
  int y;
  Pos(const int x_, const int y_) : x{x_}, y{y_} {}
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

inline std::unordered_map<Tetromino, Color> colors{{Tetromino::O, RED},
                                                   {Tetromino::I, BLUE},
                                                   {Tetromino::T, GREEN},
                                                   {Tetromino::L, ORANGE},
                                                   {Tetromino::Z, PURPLE}};

using TetrisGrid = std::vector<std::vector<Tetromino>>;

enum class Direction { Right, Left, Up, Down };

}  // namespace tetrispp
