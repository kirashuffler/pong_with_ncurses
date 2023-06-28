#pragma once

#include <array>
#include <span>
#include <cstdint>
#include "point.h"

namespace pong_game
{
class Player
{
public:
  Player& operator=(const Player&) = delete;
  Player(const Player&) = delete;
  Player& operator=(Player&&) = delete;
  Player(const Player&&) = delete;

  template<size_t N>
  Player(std::array<Point, N>& board_points,
      size_t player_index,
      size_t player_width_):
    points(std::next(board_points.begin(), player_index), player_width_)
  {
  };

  void Initialize(uint16_t x, uint16_t y);
  void Move(uint16_t diff);
  void UpdateYDiff();

  std::span<Point> points;
  int16_t d_y;

private:
  uint16_t d_y_cur_tick_ = 0;
  static constexpr uint16_t d_y_ticks_target_ = 20;
  uint16_t prev_y_;
};

} // namespace pong_game
