#ifndef PARTITION_HPP
#define PARTITION_HPP

#include <memory>
#include "shape-matrix.hpp"

namespace shilov
{
  void redistribution(ShapeMatrix& shapeMatrix);
  ShapeMatrix partition(const CompositeShape& compositeShape);
}

#endif
