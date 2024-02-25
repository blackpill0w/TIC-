#include <array>
#include <random>
#include <algorithm>
#include <fmt/core.h>
#include <raylib.h>

#include "./tetris.hpp"

using std::array;

namespace tetrispp {

[[maybe_unused]] std::string tetromino_to_string(const Tetromino t) {
  using enum Tetromino;
  switch (t) {
    case O: return "Tetromino(O)";
    case I: return "Tetromino(I)";
    case T: return "Tetromino(T)";
    case L: return "Tetromino(L)";
    case Z: return "Tetromino(Z)";
    case S: return "Tetromino(S)";
    default: return "Tetromino(None)";
  }
}

[[maybe_unused]] std::string pos_to_string(const Pos pos) {
  return "Pos(x: " + std::to_string(pos.x) + ", y: " + std::to_string(pos.y) + ")";
}

[[maybe_unused]] std::string direction_to_string(const Direction d) {
  using enum Direction;
  switch (d) {
    case Right: return "Direction(Right)";
    case Left: return "Direction(Left)";
    case Up: return "Direction(Up)";
    default: return "Direction(Down)";
  }
}

[[maybe_unused]] std::string falling_tetromino_data_to_string(const FallingTetrominoData &ftd) {
  return "FallingTetrominoData(" + tetromino_to_string(ftd.type) + ", " +
         direction_to_string(ftd.d) + ", " + pos_to_string(ftd.pos) + ", " +
         tetromino_to_string(ftd.next) + ", " + direction_to_string(ftd.next_d) + ")";
}

void init_grid(TetrisGrid &grid) {
  grid.reserve(GRID_HEIGHT);
  for (unsigned l = 0; l < GRID_HEIGHT; ++l) {
    if (grid.size() <= l) {
      grid.emplace_back();
      grid[l].reserve(GRID_WIDTH);
    }
    for (unsigned c = 0; c < GRID_WIDTH; ++c) {
      if (grid[l].size() <= c) {
        grid[l].push_back(Tetromino::None);
      } else {
        grid[l][c] = Tetromino::None;
      }
    }
  }
}

void print_grid(const TetrisGrid &grid) {
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

void draw_grid(const TetrisGrid &grid, const size_t x_offset, const size_t y_offset) {
  size_t x = 0, y = 0;
  for (const auto &l : grid) {
    x = 0;
    for (const auto c : l) {
      if (c != Tetromino::None) {
        DrawRectangle(x + x_offset, y + y_offset, SQUARE_SIZE, SQUARE_SIZE, colors[c]);
        DrawRectangleLines(
            x + x_offset, y + y_offset, SQUARE_SIZE, SQUARE_SIZE, colors[Tetromino::None]
        );
      }
      x += SQUARE_SIZE;
    }
    y += SQUARE_SIZE;
  }
}

void draw_tetromino_at(
    const Tetromino t, const Direction d, const size_t x, const size_t y,
    const std::optional<Color> c
) {
  const array<Pos, 4> positions =
      get_full_positions_of_tetromino(t, d, x / SQUARE_SIZE, y / SQUARE_SIZE);
  for (auto &pos : positions) {
    DrawRectangle(
        pos.x * SQUARE_SIZE, pos.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, c ? *c : colors[t]
    );
    DrawRectangleLines(
        pos.x * SQUARE_SIZE, pos.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, colors[Tetromino::None]
    );
  }
}

array<Pos, 4> get_full_positions_of_tetromino(
    const Tetromino t, const Direction d, const size_t x, const size_t y
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
        case Left: return {Pos{x + 1, y}, {x + 1, y + 1}, {x + 1, y + 2}, {x, y + 1}};
        case Up: return {Pos{x + 1, y}, {x + 1, y + 1}, {x + 2, y + 1}, {x, y + 1}};
        case Down: return {Pos{x, y}, {x + 1, y}, {x + 2, y}, {x + 1, y + 1}};
      }
      [[fallthrough]];
    case Tetromino::L:
      switch (d) {
        case Right: return {Pos{x, y}, {x, y + 1}, {x, y + 2}, {x + 1, y + 1}};
        case Left: return {Pos{x, y}, {x, y + 1}, {x + 1, y + 1}, {x + 1, y + 2}};
        case Up: return {Pos{x, y + 1}, {x + 1, y + 1}, {x + 2, y + 1}, {x + 2, y}};
        case Down: return {Pos{x, y}, {x, y + 1}, {x + 1, y}, {x + 2, y}};
      }
      [[fallthrough]];

    case Tetromino::Z:
      switch (d) {
        case Right: [[fallthrough]];
        case Left: return {Pos{x, y}, {x + 1, y}, {x + 1, y + 1}, {x + 2, y + 1}};
        case Up: [[fallthrough]];
        case Down: return {Pos{x + 1, y}, {x + 1, y + 1}, {x, y + 1}, {x, y + 2}};
      }
      [[fallthrough]];
    case Tetromino::S:
      switch (d) {
        case Right: [[fallthrough]];
        case Left: return {Pos{x, y + 1}, {x + 1, y + 1}, {x + 1, y}, {x + 2, y}};
        case Up: [[fallthrough]];
        case Down: return {Pos{x, y}, {x + 1, y}, {x + 1, y + 1}, {x + 1, y + 2}};
      }
      [[fallthrough]];
    default: return {Pos{x, y}, {x, y}, {x, y}, {x, y}};
  }
}

void put_tetromino_at(
    TetrisGrid &grid, const Tetromino t, const Direction d, const size_t x, const size_t y
) {
  const array<Pos, 4> positions = get_full_positions_of_tetromino(t, d, x, y);
  for (auto &pos : positions) {
    grid[pos.y][pos.x] = t;
  }
}

bool can_move_tetromino_to(
    TetrisGrid &grid, const Tetromino t, const Direction d, const size_t x, const size_t y,
    const Direction mov_d
) {
  using enum Direction;
  const size_t nx = mov_d == Right ? x + 1 : mov_d == Left ? x - 1 : x;
  const size_t ny = mov_d == Down ? y + 1 : mov_d == Down ? y - 1 : y;
  clear_tetromino_at(grid, t, d, x, y);

  const array<Pos, 4> future_positions = get_full_positions_of_tetromino(t, d, nx, ny);
  bool res                             = true;

  for (const auto &pos : future_positions) {
    if (pos.y >= grid.size() or pos.x >= grid[0].size() or grid[pos.y][pos.x] != Tetromino::None) {
      res = false;
      break;
    }
  }
  put_tetromino_at(grid, t, d, x, y);
  return res;
}

bool can_put_tetromino_at(
    TetrisGrid &grid, const Tetromino t, const Direction d, const size_t x, const size_t y
) {
  const array<Pos, 4> positions = get_full_positions_of_tetromino(t, d, x, y);

  for (const auto &pos : positions) {
    fmt::println("{}", pos_to_string(pos));
    if (pos.y >= grid.size() or pos.x >= grid[0].size() or grid[pos.y][pos.x] != Tetromino::None) {
      return false;
    }
  }
  fmt::println("-------");
  return true;
}

void clear_tetromino_at(
    TetrisGrid &grid, const Tetromino t, const Direction d, const size_t x, const size_t y
) {
  const array<Pos, 4> positions = get_full_positions_of_tetromino(t, d, x, y);
  for (auto &pos : positions) {
    grid[pos.y][pos.x] = Tetromino::None;
  }
}

static size_t randn(const size_t min, const size_t max) {
  static std::random_device rd;
  static std::mt19937_64 generator(rd());
  std::uniform_int_distribution<size_t> random_number(min, max);
  return random_number(generator);
}

FallingTetrominoData new_falling_tetromino(
    const TetrisGrid &grid, const Tetromino type, const std::optional<Direction> d
) {
  FallingTetrominoData ftd{
      .type   = type == Tetromino::None
                    ? static_cast<Tetromino>(randn(0, static_cast<size_t>(Tetromino::None) - 1))
                    : type,
      .d      = d.has_value() ? static_cast<Direction>(randn(0, 3)) : *d,
      .pos    = Pos{randn(0, grid[0].size() - 1), 0},
      .next   = static_cast<Tetromino>(randn(0, static_cast<size_t>(Tetromino::None) - 1)),
      .next_d = static_cast<Direction>(randn(0, 3)),
  };

  // x+1 O: x+=1, T: R/L x+1, L: R/L x+1, Z: R/L x+1, S: U/D x+1, Z: D/U
  // x+2: T: U/D, L: U/D, Z: R/L, S: R/L x+2
  // x+3: I: U/D

  // Cases when we need more x+N cases
  const bool need_one_more_x = (ftd.type == Tetromino::O) or
                               ((ftd.type == Tetromino::Z or ftd.type == Tetromino::S) and
                                (ftd.d == Direction::Up or ftd.d == Direction::Down)) or
                               ((ftd.d == Direction::Right or ftd.d == Direction::Left) and
                                (ftd.type == Tetromino::T or ftd.type == Tetromino::L));
  const bool need_two_more_x = ((ftd.type == Tetromino::Z or ftd.type == Tetromino::S) and
                                (ftd.d == Direction::Right or ftd.d == Direction::Left)) or
                               ((ftd.d == Direction::Up or ftd.d == Direction::Down) and
                                (ftd.type == Tetromino::T or ftd.type == Tetromino::L));
  const bool need_three_more_x =
      ftd.type == Tetromino::I and (ftd.d == Direction::Up or ftd.d == Direction::Down);

  const auto add_n_to_x_if_needed = [&](const size_t x, const size_t n) {
    return x > (grid[0].size() - n - 1) ? (grid[0].size() - n - 1) : x;
  };

  if (need_three_more_x) {
    ftd.pos.x = add_n_to_x_if_needed(ftd.pos.x, 3);
  } else if (need_two_more_x) {
    ftd.pos.x = add_n_to_x_if_needed(ftd.pos.x, 2);
  } else if (need_one_more_x) {
    ftd.pos.x = add_n_to_x_if_needed(ftd.pos.x, 1);
  }

  return ftd;
}

void clear_full_lines(TetrisGrid &grid) {
  namespace r                  = std::ranges;
  const auto grid_line_is_full = [](const std::vector<Tetromino> &v) {
    return r::all_of(v, [](Tetromino t) { return t != Tetromino::None; });
  };
  const auto grid_line_is_empty = [](const std::vector<Tetromino> &v) {
    return r::all_of(v, [](Tetromino t) { return t == Tetromino::None; });
  };

  const auto clear_full_line = [&](TetrisGrid &g, const size_t l) {
    for (size_t i = l; i != 0 or not grid_line_is_empty(g[i]); --i) {
      g[i] = g[i - 1];  // copy
    }
  };

  for (int l = grid.size() - 1; l >= 0; --l) {
    if (grid_line_is_full(grid[size_t(l)])) {
      clear_full_line(grid, size_t(l));
    }
  }
}

}  // namespace tetrispp
