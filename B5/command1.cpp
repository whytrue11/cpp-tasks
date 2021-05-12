#include "commands.hpp"

#include <iostream>
#include <iterator>
#include <string>
#include <set>

#include "str-case-comparator.hpp"

void command1(std::istream& input, std::ostream& output)
{
  std::set<std::string, StrCaseComparator>
    uniqueWords((std::istream_iterator<std::string>(input)), std::istream_iterator<std::string>());

  if (!input.eof())
  {
    throw std::ios_base::failure("Logical error on input operation or read error on input operation");
  }

  std::copy(uniqueWords.begin(), uniqueWords.end(), std::ostream_iterator<std::string>(output, "\n"));
}
