#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape
{
public:
  explicit Rectangle(const rectangle_t& rectangle);
  Rectangle(double x, double y, double width, double height);

  void move(const point_t& point) noexcept override;
  void move(double dx, double dy) noexcept override;
  point_t getPosition() const noexcept override;
  double getWidth() const noexcept;
  double getHeight() const noexcept;
  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void setWidth(double width);
  void setHeight(double height);

private:
  rectangle_t rectangle_;
};

#endif
