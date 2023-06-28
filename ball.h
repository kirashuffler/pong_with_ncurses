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
  public:
    Point& point;
    int16_t d_x = 1, d_y = 0;
    uint16_t target_ticks_x = 1, target_ticks_y = 1; //ttu - target ticks to update

  private:
    uint16_t cur_tick_x = 0, cur_tick_y = 0;
  };

} //namespace pong_game
