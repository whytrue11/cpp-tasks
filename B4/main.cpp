#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "task.hpp"

int main()
{
  std::vector<DataStruct> array((std::istream_iterator<DataStruct>(std::cin)), std::istream_iterator<DataStruct>());

  if (std::cin.bad())
  {
    std::cerr << "Irrecoverable stream error";
    return 2;
  }

  if (!std::cin.eof())
  {
    std::cerr << "Invalid format or incorrect number";
    return 1;
  }

  try
  {
    std::sort(array.begin(), array.end(), DataStructComparator());
    std::copy(array.cbegin(), array.cend(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what();
    return 2;
  }
}
