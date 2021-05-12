#include "point.hpp"

#include <iostream>

#include "tools.hpp"

std::istream& operator>>(std::istream& input, point_t& point)
{
  int x, y = 0;
  char openBracket = 'F';
  char closeBracket = 'F';
  char delimiter = 'F';

  input >> skipwsExceptNewline >> std::noskipws >> openBracket >> skipwsExceptNewline >> std::noskipws >> x
    >> skipwsExceptNewline >> std::noskipws >> delimiter >> skipwsExceptNewline >> std::noskipws >> y
    >> skipwsExceptNewline >> std::noskipws >> closeBracket;

  if (input.fail() || openBracket != '(' || delimiter != ';' || closeBracket != ')')
  {
    if (input.eof())
    {
      input.unget();
    }
    input.setstate(std::ios_base::failbit);
    return input;
  }

  point = {x, y};

  return input;
}

std::ostream& operator<<(std::ostream& output, const point_t& point)
{
  output << '(' << point.x << "; " << point.y << ')';
  return output;
}
