#include "tools.hpp"
#include <string>
#include <iostream>

bool stringToIntConverter(const std::string& string, int& integer)
{
  try
  {
    size_t pos = 0;
    integer = std::stoi(string, &pos);
    if (string.size() != pos)
    {
      return false;
    }
  }
  catch (const std::exception&)
  {
    return false;
  }
  return true;
}

std::istream& skipwsExceptNewline(std::istream& input)
{
  for (char temp = input.get(); isspace(temp) && temp != '\n'; temp = input.get())
  { }
  if (!input.eof())
  {
    input.unget();
  }
  return input;
}
