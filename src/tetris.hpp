#pragma once

#include <array>
#include "utils.hpp"

namespace tetrispp {
void init_grid(TetrisGrid &grid);
void print_grid(TetrisGrid &grid);
void draw_grid(TetrisGrid &grid, const int x_offset = 0, const int y_offset = 0);
std::array<Pos, 4> get_full_positions_of_tetromino(const Tetromino t, const Direction d,
                                                   const int x, const int y);
void put_tetromino_at(TetrisGrid &grid, const Tetromino t, const Direction d, const int x,
                      const int y);
void clear_tetromino_at(TetrisGrid &grid, const Tetromino t, const Direction d, const int x,
                        const int y);
}  // namespace tetrispp
