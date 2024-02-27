#pragma once

#include <vector>
#include <array>
#include <string>
#include <optional>
#include "utils.hpp"

namespace tetrispp {

using TetrisGrid = std::vector<std::vector<Tetromino>>;

[[maybe_unused]] std::string tetromino_to_string(const Tetromino t);
[[maybe_unused]] std::string pos_to_string(const Pos pos);
[[maybe_unused]] std::string direction_to_string(const Direction d);
[[maybe_unused]] std::string falling_tetromino_data_to_string(const FallingTetrominoData &ftd);
[[maybe_unused]] std::string grid_to_string(const TetrisGrid &grid);

void init_grid(TetrisGrid &grid);
void draw_grid(const TetrisGrid &grid, const size_t x_offset = 0, const size_t y_offset = 0);
void draw_tetromino_at(
    const Tetromino t, const Direction d, const size_t x, const size_t y, const std::optional<Color> c = std::nullopt
);

std::array<Pos, 4> get_full_positions_of_tetromino(
    const Tetromino t, const Direction d, const size_t x, const size_t y
);
bool can_move_tetromino_to(
    TetrisGrid &grid, const Tetromino t, const Direction d, const size_t x, const size_t y, const Direction mov_d
);

bool can_put_tetromino_at(TetrisGrid &grid, const Tetromino t, const Direction d, const size_t x, const size_t y);

void put_tetromino_at(TetrisGrid &grid, const Tetromino t, const Direction d, const size_t x, const size_t y);
void clear_tetromino_at(TetrisGrid &grid, const Tetromino t, const Direction d, const size_t x, const size_t y);

//** Pass `None` for `Tetromino` and/or `std::nullopt` for `Direction` if you want them randomly
//   selected
FallingTetrominoData new_falling_tetromino(
    const TetrisGrid &grid, const Tetromino type = Tetromino::None, const std::optional<Direction> d = std::nullopt
);

void clear_full_lines(TetrisGrid &grid);

Direction rotate_90deg(const Direction d);
Direction rotate_min_90deg(const Direction d);

}  // namespace tetrispp
