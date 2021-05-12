#include "rectangle.hpp"
#include <stdexcept>
#include "base-types.hpp"

inline void checkIncorrectWidth(double width)
{
  if (width <= 0)
  {
    throw std::invalid_argument("Incorrect width");
  }
}

inline void checkIncorrectHeight(double height)
{
  if (height <= 0)
  {
    throw std::invalid_argument("Incorrect height");
  }
}

Rectangle::Rectangle(const rectangle_t& rectangle) :
  rectangle_(rectangle)
{
  checkIncorrectWidth(rectangle_.width);
  checkIncorrectHeight(rectangle_.height);
}

Rectangle::Rectangle(double x, double y, double width, double height) :
  Rectangle({{x, y}, width, height})
{ }

void Rectangle::move(const point_t& point) noexcept
{
  rectangle_.pos = point;
}

void Rectangle::move(double dx, double dy) noexcept
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}

point_t Rectangle::getPosition() const noexcept
{
  return rectangle_.pos;
}

double Rectangle::getWidth() const noexcept
{
  return rectangle_.width;
}

double Rectangle::getHeight() const noexcept
{
  return rectangle_.height;
}

double Rectangle::getArea() const noexcept
{
  return rectangle_.width * rectangle_.height;
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  return rectangle_;
}

void Rectangle::setWidth(double width)
{
  checkIncorrectWidth(width);
  rectangle_.width = width;
}

void Rectangle::setHeight(double height)
{
  checkIncorrectHeight(height);
  rectangle_.height = height;
}
