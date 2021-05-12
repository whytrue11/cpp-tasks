#include <iostream>
#include <stdexcept>
#include <string>

#include "commands.hpp"
#include "tools.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Wrong number of arguments";
    return 1;
  }

  int number = 0;
  std::string numberStr = argv[1];
  if (!stringToIntConverter(numberStr, number))
  {
    std::cerr << "Incorrect number";
    return 1;
  }

  switch (number)
  {
  case 1:
  {
    try
    {
      command1(std::cin, std::cout);
    }
    catch (const std::exception& exception)
    {
      std::cerr << exception.what();
      return 2;
    }
    break;
  }

  case 2:
  {
    try
    {
      command2(std::cout);
    }
    catch (const std::exception& exception)
    {
      std::cerr << exception.what();
      return 2;
    }
    break;
  }

  default:
    std::cerr << "Incorrect number";
    return 1;
  }
  return 0;
}
