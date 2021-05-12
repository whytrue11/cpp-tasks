#include "commands.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

struct PIMultiplier
{
  double operator()(double a)
  { return a * M_PI; }
};

void command1(std::istream& input, std::ostream& output)
{
  std::vector<double> array;
  std::transform(std::istream_iterator<double>(input), std::istream_iterator<double>(), std::back_inserter(array),
    PIMultiplier());

  if (!input.eof())
  {
    throw std::ios_base::failure("Logical error on input operation or read error on input operation");
  }

  std::copy(array.begin(), array.end(), std::ostream_iterator<double>(output, " "));
  output << "\n";
}
