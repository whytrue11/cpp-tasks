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

Circle::Circle(double x, double y, double radius) :
  pos_{x, y},
  radius_(radius)
{
  checkIncorrectRadius(radius);
}

void Circle::move(const point_t& point) noexcept
{
  pos_ = point;
}

void Circle::move(double dx, double dy) noexcept
{
  pos_.x += dx;
  pos_.y += dy;
}

point_t Circle::getPosition() const noexcept
{
  return pos_;
}

double Circle::getRadius() const noexcept
{
  return radius_;
}

double Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return {pos_, radius_ * 2, radius_ * 2};
}

void Circle::setRadius(double radius)
{
  checkIncorrectRadius(radius);
  radius_ = radius;
}
