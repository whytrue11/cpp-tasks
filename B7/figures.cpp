#include "figures.hpp"

#include <ostream>

#include "point.hpp"

Shape::Shape(const point_t& point) :
  center_(point)
{ }

Circle::Circle(const point_t& point) :
  Shape(point)
{ }

Triangle::Triangle(const point_t& point) :
  Shape(point)
{ }

Square::Square(const point_t& point) :
  Shape(point)
{ }

bool Shape::isMoreLeft(const Shape& shape) const
{
  return center_.x < shape.center_.x;
}

bool Shape::isUpper(const Shape& shape) const
{
  return center_.y > shape.center_.y;
}

const point_t& Shape::getCenter() const
{
  return center_;
}

void Shape::setCenter(const point_t& point)
{
  center_ = point;
};

void Circle::draw(std::ostream& output) const
{
  output << "CIRCLE";
}

void Triangle::draw(std::ostream& output) const
{
  output << "TRIANGLE";
}

void Square::draw(std::ostream& output) const
{
  output << "SQUARE";
}
