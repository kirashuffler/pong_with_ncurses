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
  }

  void Player::Move(uint16_t diff)
  {
    for (auto& point : points)
    {
      point.y += diff;
    }
  }

}

