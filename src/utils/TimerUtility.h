#pragma once

#include <atomic>
#include <chrono>
#include <thread>

class Timer {
private:
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point pauseTime;
  std::chrono::steady_clock::duration pauseDuration = std::chrono::seconds(0);
  std::atomic<bool> alive;
  std::atomic<int> elapsedTime;
  std::atomic<int> lastTime;
  std::thread timerThread;
  bool paused = false;

  void runTimer() {
    while (alive) {
      auto currentTime = std::chrono::steady_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::seconds>(
          currentTime - startTime);
      elapsedTime = duration.count();
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }

public:
  Timer() {
    alive = false;
    elapsedTime = 0;
  }

  void start() {
    if (!alive) {
      alive = true;
      startTime = std::chrono::steady_clock::now();
      timerThread = std::thread(&Timer::runTimer, this);
    }
  }

  void stop() {
    if (alive) {
      alive = false;
      if (timerThread.joinable()) {
        timerThread.join();
      }
    }
  }

  void pause() {
    paused = true;
    lastTime = elapsedTime.load();
    if (alive) {
      pauseTime = std::chrono::steady_clock::now();
    }
  }

  void resume() {
    if (alive) {
      auto currentTime = std::chrono::steady_clock::now();
      pauseDuration += currentTime - pauseTime;
    }
    paused = false;
  }

  void reset() {
    startTime = std::chrono::steady_clock::now();
    pauseDuration = std::chrono::seconds(0);
  }

  bool getStatus() { return paused; }

  int getElapsedTime() {
    if (paused) {
      return lastTime.load();
    } else {
      return elapsedTime.load();
    }
  }
};
