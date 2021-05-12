#include "commands.hpp"
#include <iostream>
#include <list>
#include <stdexcept>

void command2(std::istream& input, std::ostream& output)
{
  int temp = 0;
  std::list<int> list;
  while (input >> temp)
  {
    if (temp < 1 || temp > 20)
    {
      throw std::invalid_argument("Value too small or big");
    }
    list.push_back(temp);
  }
  if (!input.eof())
  {
    throw std::invalid_argument("Logical error on input operation or read error on input operation");
  }

  if (list.size() > 20)
  {
    throw std::invalid_argument("Too many values entered");
  }

  if (list.empty())
  {
    return;
  }

  for (auto frontIt = list.begin(), backIt = list.end(); frontIt != backIt; ++frontIt)
  {
    output << *frontIt << " ";
    if (frontIt == --backIt)
    {
      break;
    }
    output << *backIt << " ";
  }

  output << "\n";
}
