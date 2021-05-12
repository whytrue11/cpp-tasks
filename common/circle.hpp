#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace shilov
{
  class Circle : public Shape
  {
  public:
    Circle(double x, double y, double radius);

    void move(const point_t& point) noexcept override;
    void move(double dx, double dy) noexcept override;
    point_t getPosition() const noexcept override;
    double getRadius() const noexcept;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void setRadius(double radius);
    void scale(double coefficient) override;
    void rotate(double angle) noexcept override;
  private:
    point_t pos_;
    double radius_;
  };
}

#endif
