#include "player.h"

namespace pong_game
{
  void Player::Initialize(uint16_t x, uint16_t y)
  {
    uint16_t i = 0;
    for (auto& point : points)
    {
      point.x = x;
      point.y = y + i++;
      point.ch = '#';
    }
    prev_y_ = y;
  }

  void Player::Move(uint16_t diff)
  {
    for (auto& point : points)
    {
      point.y += diff;
    }
  }

  void Player::UpdateYDiff()
  {
    ++d_y_cur_tick_;
    d_y_cur_tick_ %= d_y_ticks_target_;
    if (d_y_cur_tick_ == 0)
    {
      auto diff = static_cast<int16_t>(points.front().y) - static_cast<int16_t>(prev_y_);
      d_y = (diff > 0) - (diff < 0);
      if (diff != 0)
        prev_y_ = points.front().y;
    }
  }

} // namespace pong_game
