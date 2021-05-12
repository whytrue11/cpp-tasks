#include "composite-shape.hpp"

#include <limits>
#include <stdexcept>
#include <cmath>
#include <memory>
#include "base-types.hpp"

shilov::CompositeShape::CompositeShape(const shilov::CompositeShape& compositeShape) :
  shapeArray_(std::make_unique<std::shared_ptr<Shape>[]>(compositeShape.capacity_)),
  size_(compositeShape.size_),
  capacity_(compositeShape.capacity_)
{
  for (size_t i = 0; i < size_; ++i)
  {
    shapeArray_[i] = compositeShape[i];
  }
}

shilov::CompositeShape& shilov::CompositeShape::operator=(const shilov::CompositeShape& compositeShape)
{
  if (&compositeShape == this)
  {
    return *this;
  }

  if (capacity_ < compositeShape.capacity_)
  {
    shapeArray_ = std::make_unique<std::shared_ptr<Shape>[]>(compositeShape.capacity_);
    capacity_ = compositeShape.capacity_;
  }

  size_t i = 0;
  for (; i < compositeShape.size_; ++i)
  {
    shapeArray_[i] = compositeShape[i];
  }
  for (; i < size_; ++i)
  {
    shapeArray_[i].reset();
  }
  size_ = compositeShape.size_;
  return *this;
}

std::shared_ptr<shilov::Shape> shilov::CompositeShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Array index out of bounds");
  }
  return shapeArray_[index];
}

void shilov::CompositeShape::move(const shilov::point_t& point) noexcept
{
  point_t compositeShapePosition = getPosition();
  move(point.x - compositeShapePosition.x, point.y - compositeShapePosition.y);
}

void shilov::CompositeShape::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < size_; ++i)
  {
    shapeArray_[i]->move(dx, dy);
  }
}

shilov::point_t shilov::CompositeShape::getPosition() const noexcept
{
  return getFrameRect().pos;
}

double shilov::CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (size_t i = 0; i < size_; ++i)
  {
    area += shapeArray_[i]->getArea();
  }
  return area;
}

shilov::rectangle_t shilov::CompositeShape::getFrameRect() const noexcept
{
  point_t topRightPoint{std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()};
  point_t bottomLeftPoint{std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()};
  size_t i = 0;
  for (; i < size_; ++i)
  {
    rectangle_t shapeFrameRect = shapeArray_[i]->getFrameRect();
    if (!(std::isnan(shapeFrameRect.width) && std::isnan(shapeFrameRect.height) &&
      std::isnan(shapeFrameRect.pos.x) &&
      std::isnan(shapeFrameRect.pos.y)))
    {
      topRightPoint = {shapeFrameRect.pos.x + shapeFrameRect.width / 2,
        shapeFrameRect.pos.y + shapeFrameRect.height / 2};
      bottomLeftPoint = {shapeFrameRect.pos.x - shapeFrameRect.width / 2,
        shapeFrameRect.pos.y - shapeFrameRect.height / 2};
      ++i;
      break;
    }
  }
  for (; i < size_; ++i)
  {
    rectangle_t shapeFrameRect = shapeArray_[i]->getFrameRect();
    point_t shapeFrameRectTopRightPoint{shapeFrameRect.pos.x + shapeFrameRect.width / 2,
      shapeFrameRect.pos.y + shapeFrameRect.height / 2};
    point_t shapeFrameRectBottomLeftPoint{shapeFrameRect.pos.x - shapeFrameRect.width / 2,
      shapeFrameRect.pos.y - shapeFrameRect.height / 2};

    if (topRightPoint.x < shapeFrameRectTopRightPoint.x)
    {
      topRightPoint.x = shapeFrameRectTopRightPoint.x;
    }

    if (topRightPoint.y < shapeFrameRectTopRightPoint.y)
    {
      topRightPoint.y = shapeFrameRectTopRightPoint.y;
    }

    if (bottomLeftPoint.x > shapeFrameRectBottomLeftPoint.x)
    {
      bottomLeftPoint.x = shapeFrameRectBottomLeftPoint.x;
    }

    if (bottomLeftPoint.y > shapeFrameRectBottomLeftPoint.y)
    {
      bottomLeftPoint.y = shapeFrameRectBottomLeftPoint.y;
    }
  }
  double width = topRightPoint.x - bottomLeftPoint.x;
  double height = topRightPoint.y - bottomLeftPoint.y;

  return {{bottomLeftPoint.x + width / 2, bottomLeftPoint.y + height / 2}, width, height};
}

void shilov::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Incorrect scale coefficient");
  }
  point_t frameRectPosition = getFrameRect().pos;
  for (size_t i = 0; i < size_; ++i)
  {
    double dx = (shapeArray_[i]->getPosition().x - frameRectPosition.x) * (coefficient - 1);
    double dy = (shapeArray_[i]->getPosition().y - frameRectPosition.y) * (coefficient - 1);
    shapeArray_[i]->move(dx, dy);
    shapeArray_[i]->scale(coefficient);
  }
}

void shilov::CompositeShape::rotate(double angle) noexcept
{
  point_t compositeShapePosition = getPosition();
  double sin = std::sin(M_PI / 180 * angle);
  double cos = std::cos(M_PI / 180 * angle);
  for (size_t i = 0; i < size_; ++i)
  {
    point_t abstractShapePosition = shapeArray_[i]->getPosition();
    abstractShapePosition.x -= compositeShapePosition.x;
    abstractShapePosition.y -= compositeShapePosition.y;
    shapeArray_[i]->move({compositeShapePosition.x + abstractShapePosition.x * cos - abstractShapePosition.y * sin,
      compositeShapePosition.y + abstractShapePosition.x * sin + abstractShapePosition.y * cos});
    shapeArray_[i]->rotate(angle);
  }
}

void shilov::CompositeShape::pushBack(const std::shared_ptr<Shape>& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("The shape to add must not be an null pointer");
  }
  if (shape.get() == this)
  {
    throw std::invalid_argument("Can't put a pointer inside itself");
  }

  if (isEmpty())
  {
    shapeArray_ = std::make_unique<std::shared_ptr<Shape>[]>(1);
    capacity_ = 1;
    shapeArray_[size_++] = shape;
  }
  else if (capacity_ != size_)
  {
    shapeArray_[size_++] = shape;
  }
  else
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> tempShapeArray = std::make_unique<std::shared_ptr<Shape>[]>(
      capacity_ * 2);
    capacity_ *= 2;
    for (size_t i = 0; i < size_; ++i)
    {
      tempShapeArray[i] = shapeArray_[i];
    }
    shapeArray_ = std::move(tempShapeArray);
    shapeArray_[size_++] = shape;
  }
}

void shilov::CompositeShape::popBack()
{
  if (isEmpty())
  {
    throw std::out_of_range("Composite shape must be not empty");
  }
  shapeArray_[--size_].reset();
}

bool shilov::CompositeShape::isEmpty() const noexcept
{
  return size_ == 0;
}

size_t shilov::CompositeShape::size() const noexcept
{
  return size_;
}
