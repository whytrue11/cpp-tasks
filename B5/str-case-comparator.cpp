#include "str-case-comparator.hpp"

#include <string>
#include <cctype>

bool StrCaseComparator::operator()(const std::string& a, const std::string& b) const
{
  for (auto i = a.begin(), j = b.begin(); i != a.end() || j != b.end(); ++i, ++j)
  {
    if (std::tolower(*i) != std::tolower(*j))
    {
      return std::tolower(*i) < std::tolower(*j);
    }
  }
  return a.size() < b.size();
}
