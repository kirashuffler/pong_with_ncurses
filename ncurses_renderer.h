#pragma once
#include <chrono>
#include <functional>
#include <mutex>
#include <ncurses.h>
#include <thread>
#include <unordered_map>
#include <vector>
#include <span>

#include "point.h"

class NcursesRenderer {
public:
  template<size_t N>
  NcursesRenderer(uint16_t window_height, uint16_t window_width,
                  uint frame_delay, std::span<const Point, N> points)
      : window_height_(window_height), window_width_(window_width),
        frame_delay_(frame_delay), points_(points) {
    initscr();
    /* raw(); */
    noecho();
    cbreak();
    notimeout(stdscr, TRUE);
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    refresh();
    main_window_ = newwin(window_height_, window_width_, 0, 0);
    nodelay(main_window_, TRUE);
    box(main_window_, 0, 0);
    wrefresh(main_window_);
  }

  void AddInputListener(char key, std::function<void(void)> callback) {
    input_callbacks_.try_emplace(key, callback);
  }

  ~NcursesRenderer() {
    delwin(main_window_);
    endwin();
  }

  void RunRenderer() {
    int input_key;
    while (1) {
      wclear(main_window_);
      box(main_window_, 0, 0);
      std::this_thread::sleep_for(frame_delay_);
      input_key = getch();
      for (auto& cb : single_frame_update_callbacks_)
        cb();
      if (input_callbacks_.find(input_key) != input_callbacks_.end())
        input_callbacks_.at(input_key)();
      RenderOneFrame();
    }
  }

  void AddFrameUpdateListener(std::function<void(void)> callback)
  {
    single_frame_update_callbacks_.emplace_back(callback);
  }

private:
  void RenderOneFrame() {
    for (const auto &point : points_)
      mvwaddch(main_window_, point.y, point.x, point.ch);
    wrefresh(main_window_);
    refresh();
  }

private:
  uint16_t window_height_;
  uint16_t window_width_;
  std::chrono::milliseconds frame_delay_;
  /* const std::array<Point, BufferSize> &points_; */
  std::span<const Point> points_;
  WINDOW *main_window_;
  std::mutex mtx_;
  std::unordered_map<int, std::function<void(void)>> input_callbacks_;
  std::vector<std::function<void(void)>> single_frame_update_callbacks_;
};
