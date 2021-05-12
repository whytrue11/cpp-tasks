#include "shape-matrix.hpp"

#include <stdexcept>
#include <memory>
#include "base-types.hpp"

shilov::ShapeMatrix::ShapeMatrix(const shilov::ShapeMatrix& shapeMatrix) :
  shapeMatrix_(std::make_unique<std::shared_ptr<Shape>[]>(shapeMatrix.lines_ * shapeMatrix.columns_)),
  lines_(shapeMatrix.lines_),
  columns_(shapeMatrix.columns_)
{
  for (size_t i = 0; i < lines_ * columns_; ++i)
  {
    shapeMatrix_[i] = shapeMatrix.shapeMatrix_[i];
  }
}

shilov::ShapeMatrix::ShapeMatrix(size_t lines, size_t columns) :
  shapeMatrix_(std::make_unique<std::shared_ptr<Shape>[]>(lines * columns)),
  lines_(lines),
  columns_(columns)
{
  if (lines == 0 || columns == 0)
  {
    throw std::logic_error("One of the parameters cannot be zero");
  }
}

shilov::ShapeMatrix& shilov::ShapeMatrix::operator=(const shilov::ShapeMatrix& shapeMatrix)
{
  if (&shapeMatrix == this)
  {
    return *this;
  }

  if (lines_ * columns_ < shapeMatrix.lines_ * shapeMatrix.columns_)
  {
    shapeMatrix_ = std::make_unique<std::shared_ptr<Shape>[]>(shapeMatrix.lines_ * shapeMatrix.columns_);
    lines_ = shapeMatrix.lines_;
    columns_ = shapeMatrix.columns_;
  }

  size_t i = 0;
  for (; i < shapeMatrix.lines_ * shapeMatrix.columns_; ++i)
  {
    shapeMatrix_[i] = shapeMatrix.shapeMatrix_[i];
  }
  for (; i < lines_ * columns_; ++i)
  {
    shapeMatrix_[i].reset();
  }
  lines_ = shapeMatrix.lines_;
  columns_ = shapeMatrix.columns_;
  return *this;
}

size_t shilov::ShapeMatrix::getLines() const noexcept
{
  return lines_;
}

size_t shilov::ShapeMatrix::getColumns() const noexcept
{
  return columns_;
}

std::shared_ptr<shilov::Shape>& shilov::ShapeMatrix::cell(size_t line, size_t number)
{
  if (line >= lines_ || number >= columns_)
  {
    throw std::out_of_range("Matrix index out of bounds");
  }
  return shapeMatrix_[line * columns_ + number];
}

void shilov::ShapeMatrix::resize(size_t lines, size_t columns)
{
  if (lines < lines_ || columns < columns_)
  {
    throw std::invalid_argument("The passed parameters are smaller than existing ones");
  }
  else if (lines == lines_ && columns == columns_)
  {
    return;
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> tempShapeMatrix = std::make_unique<std::shared_ptr<Shape>[]>(
    lines * columns);
  for (size_t i = 0; i < lines_; ++i)
  {
    for (size_t j = 0; j < columns_; ++j)
    {
      tempShapeMatrix[i * columns + j] = cell(i, j);
    }
  }
  shapeMatrix_ = std::move(tempShapeMatrix);
  lines_ = lines;
  columns_ = columns;
}
