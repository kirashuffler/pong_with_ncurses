#include "pong_board.h"

namespace pong_game
{

  PongBoard::PongBoard(uint16_t height, uint16_t width) :
    height_(height), width_(width),
    border_left_x_(0), border_right_x_(width - 1),
    border_top_y_(0), border_bottom_y_(height - 1),
    player1_(points_, player1_index_, player_width_),
    player2_(points_, player2_index_, player_width_)
  {
    uint16_t player_y_pos = height_ / 2 - player_width_ + 1;
    player1_.Initialize(border_left_x_ + 1, player_y_pos);
    player2_.Initialize(border_right_x_ - 1, player_y_pos);
    // initialize ball
    points_[ball_index_].x = points_[player1_index_].x + 1;
    points_[ball_index_].y = points_[player1_index_].y + 1;
    points_[ball_index_].ch = '0';
  };

  const PongBoard::points_array& PongBoard::GetPointsBuffer() const
  {
    return points_;
  }

  bool PongBoard::CollisionBottomBorder(Point& point)
  {
    return (point.y >= border_bottom_y_ - 1);
  }

  bool PongBoard::CollisionTopBorder(Point& point)
  {
    return (point.y <= border_top_y_ + 1);
  }

  bool PongBoard::CollisionTopBorderPlayer(Player& player)
  {
    return CollisionTopBorder(player.points.front());
  }

  bool PongBoard::CollisionBottomBorderPlayer(Player& player)
  {
    return CollisionBottomBorder(player.points.back());
  }

} // namespace pong_game
