#include "point.h"
#include <array>
#include <span>
#include <iterator>
#include "player.h"
#include <cstdint>

namespace pong_game
{
  using std::uint16_t;

  class PongBoard
  {
    private: // constants
      static constexpr size_t player_width_ = 3;
      static constexpr size_t ball_index_ = 0;
      static constexpr size_t player1_index_ = 1;
      static constexpr size_t player2_index_ = player1_index_ + player_width_;

      using points_array = std::array<Point, player2_index_ + player_width_>;

    public:
      enum class PlayerDirection
      {
        UP = -1,
        DOWN = 1,
      };

      enum class PlayerType
      {
        ONE = player1_index_,
        TWO = player2_index_,
      };

    public:
      PongBoard& operator=(const PongBoard&) = delete;
      PongBoard(const PongBoard&) = delete;
      PongBoard& operator=(PongBoard&&) = delete;
      PongBoard(const PongBoard&&) = delete;

      PongBoard(uint16_t height, uint16_t width);

      const points_array& GetPointsBuffer() const;

      template<PlayerType CurrentPlayer, PlayerDirection Direction>
      void MovePlayer()
      {
        auto& cur_player = CurrentPlayer == PlayerType::ONE ? player1_ : player2_;
        if (Direction == PlayerDirection::UP && CollisionTopBorderPlayer(cur_player))
          return;

        if (Direction == PlayerDirection::DOWN && CollisionBottomBorderPlayer(cur_player))
          return;

        cur_player.Move(static_cast<int>(Direction));
      };

    private:

      bool CollisionBottomBorder(Point& point);

      bool CollisionTopBorder(Point& point);

      bool CollisionTopBorderPlayer(Player& player);

      bool CollisionBottomBorderPlayer(Player& player);

    private:
      uint16_t height_;
      uint16_t width_;

      const uint16_t border_left_x_;
      const uint16_t border_right_x_;

      const uint16_t border_top_y_;
      const uint16_t border_bottom_y_;

      points_array points_;

      Player player1_, player2_;
  };

} //namespace pong_game
