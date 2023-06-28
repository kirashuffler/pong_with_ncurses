#include "ball.h"

namespace pong_game
{

  Ball::Ball(Point& point) :
    point(point)
  {
  }

  void Ball::SetXY(uint16_t x, uint16_t y)
  {
    x_float_ = static_cast<float>(x);
    y_float_ = static_cast<float>(y);
  }

  void Ball::UpdatePosition()
  {
    x_float_ += d_x;
    y_float_ += d_y;
    point.x = static_cast<uint16_t>(x_float_);
    point.y = static_cast<uint16_t>(y_float_);
  }

}// namespace pong_game
