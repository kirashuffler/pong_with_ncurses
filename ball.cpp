#include "ball.h"

namespace pong_game
{

  Ball::Ball(Point& point) :
    point(point)
  {
  };

  void Ball::UpdatePosition()
  {
    ++cur_tick_x;
    cur_tick_x %= target_ticks_x;

    ++cur_tick_y;
    cur_tick_y %= target_ticks_y;

    if (cur_tick_x == 0)
      point.x += d_x;
    if (cur_tick_y == 0)
      point.y += d_y;
  };

}// namespace pong_game
