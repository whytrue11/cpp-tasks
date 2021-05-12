#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>
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

shilov::Rectangle::Rectangle(const rectangle_t& rectangle) :
  rectangle_(rectangle),
  rotationAngle_(0)
{
  checkIncorrectWidth(rectangle_.width);
  checkIncorrectHeight(rectangle_.height);
}

shilov::Rectangle::Rectangle(double x, double y, double width, double height) :
  Rectangle({{x, y}, width, height})
{ }

void shilov::Rectangle::move(const point_t& point) noexcept
{
  rectangle_.pos = point;
}

void shilov::Rectangle::move(double dx, double dy) noexcept
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}

shilov::point_t shilov::Rectangle::getPosition() const noexcept
{
  return rectangle_.pos;
}

double shilov::Rectangle::getWidth() const noexcept
{
  return rectangle_.width;
}

double shilov::Rectangle::getHeight() const noexcept
{
  return rectangle_.height;
}

double shilov::Rectangle::getRotationAngle() const noexcept
{
  return 180 / M_PI * rotationAngle_;
}

double shilov::Rectangle::getArea() const noexcept
{
  return rectangle_.width * rectangle_.height;
}

shilov::rectangle_t shilov::Rectangle::getFrameRect() const noexcept
{
  return {rectangle_.pos,
    std::abs(std::sin(rotationAngle_)) * rectangle_.height + std::abs(std::cos(rotationAngle_)) * rectangle_.width,
    std::abs(std::sin(rotationAngle_)) * rectangle_.width + std::abs(std::cos(rotationAngle_)) * rectangle_.height};
}

void shilov::Rectangle::setWidth(double width)
{
  checkIncorrectWidth(width);
  rectangle_.width = width;
}

void shilov::Rectangle::setHeight(double height)
{
  checkIncorrectHeight(height);
  rectangle_.height = height;
}

void shilov::Rectangle::setRotationAngle(double angle) noexcept
{
  rotationAngle_ = M_PI / 180 * angle;
}

void shilov::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Incorrect scale coefficient");
  }
  rectangle_.width *= coefficient;
  rectangle_.height *= coefficient;
}

void shilov::Rectangle::rotate(double angle) noexcept
{
  rotationAngle_ += M_PI / 180 * angle;
}
