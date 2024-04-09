#pragma once
#include <chrono>

class Timer {
private:
  std::chrono::time_point<std::chrono::steady_clock> start_time;
  std::chrono::duration<int> elapsed_time;
  bool is_running;

public:
  Timer() {
    is_running = false;
    elapsed_time = std::chrono::seconds(0);
  };

  void start() {
    if (!is_running) {
      start_time = std::chrono::steady_clock::now();
      is_running = true;
    }
  }

  void pause() {
    if (is_running) {
      auto now = std::chrono::steady_clock::now();
      elapsed_time +=
          std::chrono::duration_cast<std::chrono::seconds>(now - start_time);
      is_running = false;
    }
  }

  void reset() {
    elapsed_time = std::chrono::duration<int>::zero();
    is_running = false;
  }

  int getElapsedTime() {
    if (is_running) {
      auto now = std::chrono::steady_clock::now();
      auto time = std::chrono::duration_cast<std::chrono::seconds>(
          now - start_time + elapsed_time);
      return time.count();
    } else {
      return elapsed_time.count();
    }
  }

  bool running() { return is_running; }
};
