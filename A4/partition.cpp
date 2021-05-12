#include "partition.hpp"

#include <memory>
#include "base-types.hpp"

static bool isOverlap(const std::shared_ptr<shilov::Shape>& shape1, const std::shared_ptr<shilov::Shape>& shape2)
{
  if (shape1 == nullptr || shape2 == nullptr)
  {
    throw std::invalid_argument("The shapes must not be an null pointer");
  }
  shilov::rectangle_t frameRect1 = shape1->getFrameRect();
  shilov::rectangle_t frameRect2 = shape2->getFrameRect();
  shilov::point_t topRightPoint1 = {frameRect1.pos.x + frameRect1.width / 2,
    frameRect1.pos.y + frameRect1.height / 2};
  shilov::point_t bottomLeftPoint1 = {frameRect1.pos.x - frameRect1.width / 2,
    frameRect1.pos.y - frameRect1.height / 2};
  shilov::point_t topRightPoint2 = {frameRect2.pos.x + frameRect2.width / 2,
    frameRect2.pos.y + frameRect2.height / 2};
  shilov::point_t bottomLeftPoint2 = {frameRect2.pos.x - frameRect2.width / 2,
    frameRect2.pos.y - frameRect2.height / 2};
  return (((topRightPoint1.x >= bottomLeftPoint2.x && topRightPoint1.x <= topRightPoint2.x) ||
    (bottomLeftPoint1.x >= bottomLeftPoint2.x && bottomLeftPoint1.x <= topRightPoint2.x)) &&
    ((topRightPoint1.y >= bottomLeftPoint2.y && topRightPoint1.y <= topRightPoint2.y) ||
      (bottomLeftPoint1.y >= bottomLeftPoint2.y && bottomLeftPoint1.y <= topRightPoint2.y))) ||
    (((topRightPoint2.x >= bottomLeftPoint1.x && topRightPoint2.x <= topRightPoint1.x) ||
      (bottomLeftPoint2.x >= bottomLeftPoint1.x && bottomLeftPoint2.x <= topRightPoint1.x)) &&
      ((topRightPoint2.y >= bottomLeftPoint1.y && topRightPoint2.y <= topRightPoint1.y) ||
        (bottomLeftPoint2.y >= bottomLeftPoint1.y && bottomLeftPoint2.y <= topRightPoint1.y)));
}

static void addWithPartitioning(shilov::ShapeMatrix& shapeMatrix, const std::shared_ptr<shilov::Shape>& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("The shape to partition must not be an null pointer");
  }
  else if (shapeMatrix.getLines() == 0 && shapeMatrix.getColumns() == 0)
  {
    shapeMatrix.resize(1, 1);
    shapeMatrix.cell(0, 0) = shape;
  }
  else
  {
    size_t layers = shapeMatrix.getLines();
    size_t count = shapeMatrix.getColumns();
    for (size_t i = 0; i < layers; ++i)
    {
      for (size_t j = 0; j < count; ++j)
      {
        if (shapeMatrix.cell(i, j) == nullptr)
        {
          shapeMatrix.cell(i, j) = shape;
          return;
        }
        if (isOverlap(shape, shapeMatrix.cell(i, j)))
        {
          break;
        }
        if (j == count - 1)
        {
          shapeMatrix.resize(layers, count += 1);
          shapeMatrix.cell(i, count - 1) = shape;
          return;
        }
      }
    }
    shapeMatrix.resize(layers += 1, count);
    shapeMatrix.cell(layers - 1, 0) = shape;
  }
}

shilov::ShapeMatrix shilov::partition(const shilov::CompositeShape& compositeShape)
{
  ShapeMatrix shapeMatrix;
  for (size_t i = 0; i < compositeShape.size(); ++i)
  {
    addWithPartitioning(shapeMatrix, compositeShape[i]);
  }
  return shapeMatrix;
}

void shilov::redistribution(ShapeMatrix& shapeMatrix)
{
  ShapeMatrix tempShapeMatrix{};
  size_t layers = shapeMatrix.getLines();
  size_t count = shapeMatrix.getColumns();
  for (size_t i = 0; i < layers; ++i)
  {
    for (size_t j = 0; j < count; ++j)
    {
      std::shared_ptr<Shape>& originalMatrixCell = shapeMatrix.cell(i, j);
      if (originalMatrixCell != nullptr)
      {
        addWithPartitioning(tempShapeMatrix, originalMatrixCell);
      }
    }
  }
  shapeMatrix = std::move(tempShapeMatrix);
}
