#include "pong_board.h"
#include <cmath>

namespace pong_game
{

  PongBoard::PongBoard(uint16_t height, uint16_t width) :
    height_(height), width_(width),
    border_left_x_(0), border_right_x_(width - 1),
    border_top_y_(0), border_bottom_y_(height - 1),
    player1_(points_, player1_index_, player_width_),
    player2_(points_, player2_index_, player_width_),
    ball_(points_[ball_index_])
  {
    uint16_t player_y_pos = height_ / 2 - player_width_ + 1;
    prev_player1_y_ = player_y_pos;
    prev_player2_y_ = player_y_pos;
    player1_.Initialize(border_left_x_ + 1, player_y_pos);
    player2_.Initialize(border_right_x_ - 1, player_y_pos);
    // initialize ball
    ball_.SetXY(points_[player1_index_].x + 1,
                points_[player1_index_].y + 1);
    ball_.point.ch = '0';

    initial_points_ = points_;
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

  void PongBoard::StateUpdate()
  {
    player1_.UpdateYDiff();
    player2_.UpdateYDiff();
    HandleBallCollisions();
    ball_.UpdatePosition();
    prev_player1_y_ = player1_.points.front().y;
    prev_player2_y_ = player2_.points.front().y;
  }

  void PongBoard::HandleBallCollisions()
  {
    if ((CollisionBottomBorder(ball_.point) && ball_.d_y > 0) ||
        (CollisionTopBorder(ball_.point) && ball_.d_y < 0))
      ball_.d_y *= -1;

    // Collision with vertical borders
    if (ball_.point.x == border_left_x_ + 1 && ball_.d_x < 0)
    {
      points_ = initial_points_;
      ball_.d_x = -1;
      ball_.d_y = 0;
      ball_.SetXY(initial_points_[player2_index_].x, initial_points_[player2_index_].y + 1);
    }

    if (ball_.point.x == border_right_x_ - 1 && ball_.d_x > 0)
    {
      points_ = initial_points_;
      ball_.d_x = 1;
      ball_.d_y = 0;
      ball_.SetXY(initial_points_[player1_index_].x, initial_points_[player1_index_].y + 1);
    }

    // Collision with player one
    if (ball_.point.x == player1_.points.front().x + 1 &&
        ball_.d_x < 0 &&
        ball_.point.y >= player1_.points.front().y &&
        ball_.point.y <= player1_.points.back().y)
      HandleBallPlayerCollision(player1_);

    // Collision with player two
    if (ball_.point.x == player2_.points.front().x - 1 &&
        ball_.d_x > 0 &&
        ball_.point.y >= player2_.points.front().y &&
        ball_.point.y <= player2_.points.back().y)
      HandleBallPlayerCollision(player2_);
  }

  void PongBoard::HandleBallPlayerCollision(Player& player)
  {
    constexpr float d_y_multiplier = 0.2;
    ball_.d_y += player.d_y * d_y_multiplier;
    ball_.d_x *= -1;
    auto abs_norm = std::max(std::abs(ball_.d_y), std::abs(ball_.d_x));
    ball_.d_x /= abs_norm;
    ball_.d_y /= abs_norm;
  }
} // namespace pong_game
