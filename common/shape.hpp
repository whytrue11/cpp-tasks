#ifndef SHAPE_HPP
#define SHAPE_HPP

namespace shilov
{
  struct point_t;
  struct rectangle_t;

  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual void move(const point_t& point) noexcept = 0;
    virtual void move(double dx, double dy) noexcept = 0;
    virtual point_t getPosition() const noexcept = 0;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual void scale(double coefficient) = 0;

    virtual void rotate(double angle) noexcept = 0;
  };
}

#endif
