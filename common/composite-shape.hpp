#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include <cstddef>
#include "shape.hpp"

namespace shilov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape() noexcept = default;
    CompositeShape(const CompositeShape& compositeShape);
    CompositeShape(CompositeShape&& compositeShape) noexcept = default;
    ~CompositeShape() override = default;
    CompositeShape& operator=(const CompositeShape& compositeShape);
    CompositeShape& operator=(CompositeShape&& compositeShape) noexcept = default;

    std::shared_ptr<Shape> operator[](size_t index) const;

    void move(const point_t& point) noexcept override;
    void move(double dx, double dy) noexcept override;
    point_t getPosition() const noexcept override;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void scale(double coefficient) override;
    void rotate(double angle) noexcept override;

    void pushBack(const std::shared_ptr<Shape>& shape);
    void popBack();
    bool isEmpty() const noexcept;
    size_t size() const noexcept;
  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> shapeArray_;
    size_t size_ = 0;
    size_t capacity_ = 0;
  };
}
#endif
