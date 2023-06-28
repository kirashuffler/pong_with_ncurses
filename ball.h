#include "point.h"

namespace pong_game
{

  class Ball
  {
  public:
    Ball& operator=(const Ball&) = delete;
    Ball(const Ball&) = delete;
    Ball& operator=(Ball&&) = delete;
    Ball(const Ball&&) = delete;

    Ball(Point& point);
    void UpdatePosition();
    void SetXY(uint16_t x, uint16_t y);
  public:
    Point& point;
    float d_x = 1, d_y = 0;

  private:
    float x_float_, y_float_;
  };

} //namespace pong_game
