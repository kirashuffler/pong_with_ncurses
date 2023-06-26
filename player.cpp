#include "player.h"

namespace pong_game
{
  template <size_t N>
    Player::Player(std::array<Point, N>& board_points,
        size_t player_index,
        size_t player_width_):
      points(std::next(board_points.begin(), player_index), player_width_)
  {
  };

  void Player::Initialize(uint16_t x, uint16_t y)
  {
    uint16_t i = 0;
    for (auto& point : points)
    {
      point.x = x;
      point.y = y + i++;
      point.ch = '#';
    }
  }

  void Player::Move(uint16_t diff)
  {
    for (auto& point : points)
    {
      point.y += diff;
    }
  }

}

