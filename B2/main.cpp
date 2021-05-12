#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>

#include "commands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Wrong number of arguments";
    return 1;
  }

  int number = 0;
  try
  {
    size_t pos = 0;
    number = std::stoi(argv[1], &pos);
    if (strlen(argv[1]) != pos)
    {
      std::cerr << "Incorrect number";
      return 1;
    }
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what();
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
    break;
  }

  case 2:
  {
    try
    {
      command2(std::cin, std::cout);
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
    break;
  }

  default:
    std::cerr << "Incorrect number";
    return 1;
  }
  return 0;
}
