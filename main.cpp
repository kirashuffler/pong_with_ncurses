#include "ncurses_renderer.h"
#include "pong_board.h"

int main()
{
  using namespace pong_game;

  constexpr uint16_t main_width = 50;
  constexpr uint16_t main_height = 20;
  PongBoard board(main_height, main_width);

  /* auto renderer = NcursesRenderer(main_height, main_width, */
  /*     33, std::span(board.GetPointsBuffer())); */
  NcursesRenderer
    renderer {main_height, main_width, 33, std::span(board.GetPointsBuffer())};

  renderer.AddInputListener('a',
      std::bind(
        &PongBoard::MovePlayer<PongBoard::PlayerType::ONE, PongBoard::PlayerDirection::UP>,
        &board)
  );

  renderer.AddInputListener('z',
      std::bind(
        &PongBoard::MovePlayer<PongBoard::PlayerType::ONE, PongBoard::PlayerDirection::DOWN>,
        &board)
  );
  renderer.AddInputListener('k',
      std::bind(
        &PongBoard::MovePlayer<PongBoard::PlayerType::TWO, PongBoard::PlayerDirection::UP>,
        &board)
  );

  renderer.AddInputListener('m',
      std::bind(
        &PongBoard::MovePlayer<PongBoard::PlayerType::TWO, PongBoard::PlayerDirection::DOWN>,
        &board)
  );

  renderer.AddFrameUpdateListener(std::bind(&PongBoard::StateUpdate, &board));

  renderer.RunRenderer();
  return 0;
}
