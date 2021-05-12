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

  try
  {
    switch (number)
    {
    case 1:
    {
      command1(std::cin, std::cout);
      break;
    }

    case 2:
    {
      command2(std::cin, std::cout);
      break;
    }

    default:
      std::cerr << "Incorrect number";
      return 1;
    }
  }
  catch (const std::invalid_argument& invalidArgument)
  {
    std::cerr << invalidArgument.what();
    return 1;
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what();
    return 2;
  }
  return 0;
}
