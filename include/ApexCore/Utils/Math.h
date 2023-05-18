#pragma once
#include <cstdlib>
#include <ctime>
#include <random>

namespace ApexCore::Math {
static std::mt19937 m_engine(std::time(nullptr));
template <typename T> T rand_range(T min, T max) {
  using dist_t =
      std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>>;
  dist_t dist(min, max);
  return dist(m_engine);
}
} // namespace ApexCore::Math
