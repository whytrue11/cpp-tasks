#include "toolkit.hpp"

#include <random>
#include <chrono>

void fillRandom(double* array, int size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Array must be not nullptr");
  }
  if (size < 0)
  {
    throw std::invalid_argument("Size must be greater than or equal to zero");
  }
  static std::uniform_real_distribution<double> distribution(-1.0, 1.0);
  std::default_random_engine engine(std::chrono::steady_clock::now().time_since_epoch().count());
  for (int i = 0; i < size; ++i)
  {
    array[i] = distribution(engine);
  }
}
