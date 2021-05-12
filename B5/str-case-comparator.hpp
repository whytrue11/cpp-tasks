#ifndef STR_CASE_COMPARATOR_HPP
#define STR_CASE_COMPARATOR_HPP

#include <string>

struct StrCaseComparator
{
  bool operator()(const std::string& a, const std::string& b) const;
};

#endif
