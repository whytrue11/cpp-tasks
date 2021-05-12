#include "commands.hpp"

#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <string>
#include <memory>
#include <list>
#include <map>

#include "figures.hpp"

using shapePtr = std::shared_ptr<Shape>;
using constShapePtr = const std::shared_ptr<const Shape>;

static std::ostream& operator<<(std::ostream& output, constShapePtr& shape);
static std::istream& operator>>(std::istream& input, shapePtr& shape);

static shapePtr createCircle(const point_t& point);
static shapePtr createTriangle(const point_t& point);
static shapePtr createSquare(const point_t& point);

static bool isMoreLeft(constShapePtr& shape1, constShapePtr& shape2);
static bool isUpper(constShapePtr& shape1, constShapePtr& shape2);

void command2(std::istream& input, std::ostream& output)
{
  std::list<shapePtr> figures{std::istream_iterator<shapePtr>(input), std::istream_iterator<shapePtr>()};

  if (!input.eof())
  {
    throw std::ios_base::failure("Logical error on input operation or read error on input operation");
  }

  output << "Original:\n";
  std::copy(figures.begin(), figures.end(), std::ostream_iterator<constShapePtr>(output, "\n"));

  figures.sort(isMoreLeft);
  output << "Left-Right:\n";
  std::copy(figures.begin(), figures.end(), std::ostream_iterator<constShapePtr>(output, "\n"));

  figures.sort(std::bind(isMoreLeft, std::placeholders::_2, std::placeholders::_1));
  output << "Right-Left:\n";
  std::copy(figures.begin(), figures.end(), std::ostream_iterator<constShapePtr>(output, "\n"));

  figures.sort(isUpper);
  output << "Top-Bottom:\n";
  std::copy(figures.begin(), figures.end(), std::ostream_iterator<constShapePtr>(output, "\n"));

  figures.sort(std::bind(isUpper, std::placeholders::_2, std::placeholders::_1));
  output << "Bottom-Top:\n";
  std::copy(figures.begin(), figures.end(), std::ostream_iterator<constShapePtr>(output, "\n"));
}

std::ostream& operator<<(std::ostream& output, constShapePtr& shape)
{
  shape->draw(output);
  output << " " << shape->getCenter();
  return output;
}

std::istream& operator>>(std::istream& input, shapePtr& shape)
{
  static const std::map<std::string, shapePtr (*)(const point_t& point)> figuresCreators{
    std::make_pair("CIRCLE", createCircle),
    std::make_pair("TRIANGLE", createTriangle),
    std::make_pair("SQUARE", createSquare)};

  std::string figureStr;
  input >> std::ws;

  char symbol = 'F';
  while (input.get(symbol) && symbol != '\n' && symbol != '(' && !isspace(symbol))
  {
    figureStr.push_back(symbol);
  }

  if (figureStr.empty())
  {
    return input;
  }
  input.unget();
  if (!input)
  {
    return input;
  }

  auto figureCreatorIt = figuresCreators.find(figureStr);
  if (figureCreatorIt == figuresCreators.end())
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }

  point_t point{};
  input >> point;
  if (input.fail())
  {
    return input;
  }

  shape = figureCreatorIt->second(point);
  return input;
}

shapePtr createCircle(const point_t& point)
{
  return std::make_shared<Circle>(point);
}

shapePtr createTriangle(const point_t& point)
{
  return std::make_shared<Triangle>(point);
}

shapePtr createSquare(const point_t& point)
{
  return std::make_shared<Square>(point);
}

bool isMoreLeft(constShapePtr& shape1, constShapePtr& shape2)
{
  return shape1->isMoreLeft(*shape2);
}

bool isUpper(constShapePtr& shape1, constShapePtr& shape2)
{
  return shape1->isUpper(*shape2);
}
