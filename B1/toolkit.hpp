#ifndef PRINTVECTOR_HPP
#define PRINTVECTOR_HPP

#include <iostream>
#include <vector>

template<typename T>
void printVectorWithSpaces(const std::vector<T>& array)
{
  for (T i : array)
  {
    std::cout << i << " ";
  }
}

template<typename T>
void printVector(const std::vector<T>& array)
{
  for (T i : array)
  {
    std::cout << i;
  }
}

void fillRandom(double* array, int size);

#endif
