#ifndef SHAPE_MATRIX_HPP
#define SHAPE_MATRIX_HPP

#include <memory>
#include <cstddef>
#include "composite-shape.hpp"
#include "shape.hpp"

namespace shilov
{
  class ShapeMatrix
  {
  public:
    ShapeMatrix() noexcept = default;
    ShapeMatrix(const ShapeMatrix& shapeMatrix);
    ShapeMatrix(ShapeMatrix&& shapeMatrix) noexcept = default;
    ShapeMatrix(size_t lines, size_t columns);
    ~ShapeMatrix() = default;
    ShapeMatrix& operator=(const ShapeMatrix& shapeMatrix);
    ShapeMatrix& operator=(ShapeMatrix&& shapeMatrix) noexcept = default;

    size_t getLines() const noexcept;
    size_t getColumns() const noexcept;

    std::shared_ptr<Shape>& cell(size_t line, size_t number);
    void resize(size_t lines, size_t columns);

  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> shapeMatrix_;
    size_t lines_ = 0;
    size_t columns_ = 0;
  };
}
#endif
