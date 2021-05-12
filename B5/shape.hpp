#ifndef B5_SHAPE_HPP
#define B5_SHAPE_HPP

#include <iosfwd>
#include <vector>
#include <iostream>

struct point_t;
using Shape = std::vector<point_t>;

struct ShapeCounterForTriangleSquareRectangle;
struct ShapeUnaryPredicateToCheckFiveVertices;
struct ShapeComparator;

std::istream& operator>>(std::istream& input, Shape& shape);
std::ostream& operator<<(std::ostream& output, const Shape& shape);

bool checkTriangle(const Shape& shape) noexcept;
bool checkSquare(const Shape& shape);
bool checkRectangle(const Shape& shape);

struct ShapeCounterForTriangleSquareRectangle
{
  int quantityOfTriangles;
  int quantityOfSquares;
  int quantityOfRectangles;
  void operator()(const Shape& shape);
};

struct ShapeUnaryPredicateToCheckFiveVertices
{
  bool operator()(const Shape& shape);
};

struct ShapeComparator
{
  bool operator()(const Shape& a, const Shape& b);
};

#endif
