#include "shape.hpp"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <cmath>

#include "tools.hpp"
#include "point.hpp"

static unsigned long int getSquaredDistance(const point_t& point1, const point_t& point2);

bool ShapeComparator::operator()(const Shape& a, const Shape& b)
{
  if (a.size() != b.size())
  {
    return a.size() < b.size();
  }

  return (checkTriangle(a) && !checkTriangle(b)) || (checkSquare(a) && !checkSquare(b)) ||
    (checkRectangle(a) && !checkRectangle(b));
}

bool ShapeUnaryPredicateToCheckFiveVertices::operator()(const Shape& shape)
{
  return shape.size() == 5;
}

std::istream& operator>>(std::istream& input, Shape& shape)
{
  shape.clear();
  std::ios_base::iostate inputState = input.rdstate();

  int quantityOfPoints = 0;
  if (!(input >> std::ws >> quantityOfPoints) || quantityOfPoints <= 0)
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }
  if (input.eof())
  {
    input.clear();
    input.setstate(inputState);
    input.setstate(std::ios_base::failbit);
    return input;
  }

  point_t point{0, 0};
  for (int i = 0; i < quantityOfPoints; ++i)
  {
    inputState = input.rdstate();
    input >> point;

    if (input.fail())
    {
      if (input.eof())
      {
        input.clear();
        input.setstate(inputState);
        input.setstate(std::ios_base::failbit);
      }
      return input;
    }

    shape.push_back(point);
  }

  inputState = input.rdstate();

  if ((input >> skipwsExceptNewline).get() != '\n')
  {
    if (!(input >> std::ws).eof())
    {
      input.setstate(std::ios_base::failbit);
      return input;
    }
    else
    {
      input.clear();
      input.setstate(inputState);
    }
  }

  return input;
}

std::ostream& operator<<(std::ostream& output, const Shape& shape)
{
  output << shape.size() << "  ";
  std::copy(shape.begin(), shape.end(), std::ostream_iterator<point_t>(output, "  "));
  return output;
}

bool checkTriangle(const Shape& shape) noexcept
{
  return shape.size() == 3;
}

bool checkSquare(const Shape& shape)
{
  return checkRectangle(shape) && getSquaredDistance(shape[0], shape[1]) == getSquaredDistance(shape[1], shape[2]);
}

bool checkRectangle(const Shape& shape)
{
  if (shape.size() != 4)
  {
    return false;
  }

  unsigned long int squaredDiagonal = getSquaredDistance(shape[0], shape[2]);

  if (squaredDiagonal == getSquaredDistance(shape[1], shape[3]))
  {
    unsigned long int squaredSide[3];
    for (size_t i = 0; i < 3; ++i)
    {
      squaredSide[i] = getSquaredDistance(shape[i], shape[i + 1]);
    }

    return squaredSide[0] == squaredSide[2] && squaredSide[0] + squaredSide[1] == squaredDiagonal &&
      squaredSide[1] + squaredSide[2] == squaredDiagonal;
  }
  else
  {
    return false;
  }
}

void ShapeCounterForTriangleSquareRectangle::operator()(const Shape& shape)
{
  if (checkTriangle(shape))
  {
    ++quantityOfTriangles;
  }
  else if (checkSquare(shape))
  {
    ++quantityOfSquares;
    ++quantityOfRectangles;
  }
  else if (checkRectangle(shape))
  {
    ++quantityOfRectangles;
  }
}

unsigned long int getSquaredDistance(const point_t& point1, const point_t& point2)
{
  return static_cast<unsigned long int>(std::pow(point1.x - point2.x, 2) +
    std::pow(point1.y - point2.y, 2));
}

