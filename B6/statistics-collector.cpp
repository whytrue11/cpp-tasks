#include "statistics-collector.hpp"
#include <ostream>
#include <algorithm>
#include <numeric>

void StatisticsCollector::operator()(int a)
{
  if (size == 0)
  {
    min = a;
    max = a;
    firstEqualLast = true;

    first = a;
  }
  else
  {
    max = std::max(a, max);
    min = std::min(a, min);

    firstEqualLast = (first == a);
  }

  if (a % 2 == 0)
  {
    sumOfEven += a;
  }
  else
  {
    sumOfOdd += a;
  }

  if (a > 0)
  {
    ++countPositive;
  }
  else if (a < 0)
  {
    ++countNegative;
  }

  ++size;
}

std::ostream& operator<<(std::ostream& output, const StatisticsCollector& statistics)
{
  if (statistics.empty())
  {
    output << "No Data";
    return output;
  }

  output << "Max: " << statistics.max << "\n";
  output << "Min: " << statistics.min << "\n";
  output << "Mean: " << statistics.average() << "\n";
  output << "Positive: " << statistics.countPositive << "\n";
  output << "Negative: " << statistics.countNegative << "\n";
  output << "Odd Sum: " << statistics.sumOfOdd << "\n";
  output << "Even Sum: " << statistics.sumOfEven << "\n";
  output << "First/Last Equal: " << (statistics.firstEqualLast ? "yes" : "no");
  return output;
}

double StatisticsCollector::average() const
{
  if (empty())
  {
    return std::numeric_limits<double>::quiet_NaN();
  }
  return static_cast<double>(sumOfOdd + sumOfEven) / size;
}

bool StatisticsCollector::empty() const
{
  return size == 0;
}
