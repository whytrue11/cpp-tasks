#ifndef STATISTICS_COLLECTOR_HPP
#define STATISTICS_COLLECTOR_HPP

#include <cstddef>
#include <iosfwd>

struct StatisticsCollector
{
public:
  int max;
  int min;
  int countPositive;
  int countNegative;
  long int sumOfOdd;
  long int sumOfEven;
  bool firstEqualLast;

  void operator()(int a);
  double average() const;
  bool empty() const;

private:
  int first;
  size_t size;
};

std::ostream& operator<<(std::ostream& output, const StatisticsCollector& statistics);

#endif
