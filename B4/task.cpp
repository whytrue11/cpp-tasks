#include "task.hpp"

#include <iostream>
#include <string>
#include <cmath>

#include "tools.hpp"

std::istream& operator>>(std::istream& input, DataStruct& dataStruct)
{
  input >> std::ws;

  char comma = 'F';
  int keys[2] = {0, 0};

  for (int& key : keys)
  {
    input >> skipwsExceptNewline >> std::noskipws >> key >> skipwsExceptNewline >> std::noskipws >> comma;

    if (std::abs(key) > 5 || comma != ',' || input.fail())
    {
      input.setstate(std::ios_base::failbit);
      return input;
    }
  }

  std::string data;
  getline(input >> skipwsExceptNewline, data);

  if (!data.empty() && data.back() == '\r')
  {
    data.pop_back();
  }

  if (data.empty())
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }

  dataStruct.key1 = keys[0];
  dataStruct.key2 = keys[1];
  dataStruct.str = data;

  return input;
}

std::ostream& operator<<(std::ostream& output, const DataStruct& dataStruct)
{
  output << dataStruct.key1 << ", " << dataStruct.key2 << ", " << dataStruct.str;
  return output;
}

bool DataStructComparator::operator()(const DataStruct& a, const DataStruct& b) const noexcept
{
  if (a.key1 != b.key1)
  {
    return a.key1 < b.key1;
  }
  if (a.key2 != b.key2)
  {
    return a.key2 < b.key2;
  }
  return a.str.size() < b.str.size();
}
