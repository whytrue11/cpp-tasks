#include <iostream>
#include <algorithm>
#include <iterator>

#include "statistics-collector.hpp"

int main()
{
  StatisticsCollector statistics{};
  statistics = std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), statistics);

  if (std::cin.bad())
  {
    std::cerr << "Stream error";
    return 2;
  }
  if (!std::cin.eof())
  {
    std::cerr << "Incorrect input";
    return 1;
  }

  std::cout << statistics << "\n";

  return 0;
}
