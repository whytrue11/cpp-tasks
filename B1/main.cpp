#include <iostream>
#include <string>
#include <cstring>

#include "commands.hpp"

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    std::cerr << "Wrong quantity of arguments";
    return 1;
  }
  if (strlen(argv[1]) != 1)
  {
    std::cerr << "Incorrect number";
    return 1;
  }

  char number = argv[1][0];

  switch (number)
  {
  case '1':
  {
    if (argc != 3)
    {
      std::cerr << "Wrong quantity of arguments";
      return 1;
    }

    try
    {
      command1(argv[2]);
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

  case '2':
  {
    if (argc != 3)
    {
      std::cerr << "Wrong quantity of arguments";
      return 1;
    }

    try
    {
      command2(argv[2]);
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

  case '3':
  {
    if (argc != 2)
    {
      std::cerr << "Wrong quantity of arguments";
      return 1;
    }

    try
    {
      command3();
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

  case '4':
  {
    if (argc != 4)
    {
      std::cerr << "Wrong number of arguments";
      return 1;
    }
    std::string sizeStr = argv[3];
    try
    {
      int size = stoi(sizeStr);
      command4(argv[2], size);
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
