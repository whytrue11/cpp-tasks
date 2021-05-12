#ifndef B4_TASK_HPP
#define B4_TASK_HPP

#include <string>
#include <iosfwd>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

struct DataStructComparator
{
  bool operator()(const DataStruct& a, const DataStruct& b) const noexcept;
};

std::istream& operator>>(std::istream& input, DataStruct& dataStruct);
std::ostream& operator<<(std::ostream& output, const DataStruct& dataStruct);

#endif
