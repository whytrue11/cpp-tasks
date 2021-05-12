#ifndef B7_FIGURES_HPP
#define B7_FIGURES_HPP

#include <iosfwd>

#include "point.hpp"

class Shape
{
public:
  explicit Shape(const point_t& point);
  virtual ~Shape() = default;

  virtual void draw(std::ostream&) const = 0;
  virtual bool isMoreLeft(const Shape& shape) const;
  virtual bool isUpper(const Shape& shape) const;

  const point_t& getCenter() const;
  void setCenter(const point_t& point);

private:
  point_t center_;
};

class Circle : public Shape
{
public:
  explicit Circle(const point_t& point);
  void draw(std::ostream& output) const override;
};

class Triangle : public Shape
{
public:
  explicit Triangle(const point_t& point);
  void draw(std::ostream& output) const override;
};

class Square : public Shape
{
public:
  explicit Square(const point_t& point);
  void draw(std::ostream& output) const override;
};

#endif
