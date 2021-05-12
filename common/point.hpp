#ifndef POINT_HPP
#define POINT_HPP

#include <iosfwd>

struct point_t
{
  int x, y;
};

std::istream& operator>>(std::istream& input, point_t& point);
std::ostream& operator<<(std::ostream& output, const point_t& point);

#endif
