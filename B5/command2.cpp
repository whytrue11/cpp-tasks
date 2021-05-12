#include "commands.hpp"

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <iterator>

#include "shape.hpp"
#include "point.hpp"

void command2(std::istream& input, std::ostream& output)
{
  std::vector<Shape> shapes{std::istream_iterator<Shape>(input), std::istream_iterator<Shape>()};

  if (std::cin.bad())
  {
    throw std::ios_base::failure("Irrecoverable stream error");
  }

  if (!std::cin.eof())
  {
    throw std::invalid_argument("Invalid format or incorrect number");
  }

  int verticesCount = std::accumulate(shapes.begin(), shapes.end(), 0,
    [](int verticesCount, const Shape& shape) { return verticesCount + shape.size(); });

  ShapeCounterForTriangleSquareRectangle figuresCounter{};
  figuresCounter = std::for_each(shapes.begin(), shapes.end(), figuresCounter);

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), ShapeUnaryPredicateToCheckFiveVertices()), shapes.end());

  std::vector<point_t> points;
  std::for_each(shapes.begin(), shapes.end(), [&points](const auto& shape) { points.push_back(shape[0]); });

  std::sort(shapes.begin(), shapes.end(), ShapeComparator());

  output << "Vertices: " << verticesCount << "\n";
  output << "Triangles: " << figuresCounter.quantityOfTriangles << "\n";
  output << "Squares: " << figuresCounter.quantityOfSquares << "\n";
  output << "Rectangles: " << figuresCounter.quantityOfRectangles << "\n";
  output << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<point_t>(output, "  "));

  output << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(output, "\n"));
}
