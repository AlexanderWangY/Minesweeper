#pragma once
#include <random>

inline int getRandomNumber(int min, int max) {
  std::random_device dev;
  std::mt19937 rng(dev());

  std::uniform_int_distribution<std::mt19937::result_type> distr(min, max);

  return distr(rng);
}
