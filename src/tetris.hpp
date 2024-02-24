#pragma once

#include <vector>
#include <array>
#include "utils.hpp"

namespace tetrispp {

using TetrisGrid = std::vector<std::vector<Tetromino>>;

void init_grid(TetrisGrid &grid);
void print_grid(TetrisGrid &grid);
void draw_grid(TetrisGrid &grid, const int x_offset = 0, const int y_offset = 0);
void draw_tetromino_at(const Tetromino t, const Direction d, const int x, const int y);
std::array<Pos, 4> get_full_positions_of_tetromino(
    const Tetromino t, const Direction d, const size_t x, const size_t y
);
void put_tetromino_at(
    TetrisGrid &grid, const Tetromino t, const Direction d, const size_t x, const size_t y
);
void clear_tetromino_at(
    TetrisGrid &grid, const Tetromino t, const Direction d, const size_t x, const size_t y
);
}  // namespace tetrispp
