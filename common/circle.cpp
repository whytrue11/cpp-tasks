#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>
#include "base-types.hpp"

inline void checkIncorrectRadius(double radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Incorrect radius");
  }
}

shilov::Circle::Circle(double x, double y, double radius) :
  pos_{x, y},
  radius_(radius)
{
  checkIncorrectRadius(radius);
}

void shilov::Circle::move(const point_t& point) noexcept
{
  pos_ = point;
}

void shilov::Circle::move(double dx, double dy) noexcept
{
  pos_.x += dx;
  pos_.y += dy;
}

shilov::point_t shilov::Circle::getPosition() const noexcept
{
  return pos_;
}

double shilov::Circle::getRadius() const noexcept
{
  return radius_;
}

double shilov::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

shilov::rectangle_t shilov::Circle::getFrameRect() const noexcept
{
  return {pos_, radius_ * 2, radius_ * 2};
}

void shilov::Circle::setRadius(double radius)
{
  checkIncorrectRadius(radius);
  radius_ = radius;
}

void shilov::Circle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Incorrect scale coefficient");
  }
  radius_ *= coefficient;
}

void shilov::Circle::rotate(double) noexcept
{ }
