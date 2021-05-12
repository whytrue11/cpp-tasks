#include <iostream>
#include <memory>
#include <stdexcept>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "shape-matrix.hpp"
#include "partition.hpp"

inline void testShape(shilov::Shape& shape);
inline void printMatrixComponentsFrameRects(shilov::ShapeMatrix& shapeMatrix);

int main()
{
  std::shared_ptr<shilov::Circle> circle;
  std::shared_ptr<shilov::Shape> rectangle;
  try
  {
    circle = std::make_shared<shilov::Circle>(1, 1.5, 3);
    rectangle = std::make_shared<shilov::Rectangle>(12, 18.3, 4, 20.5);
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what();
    return 1;
  }
  std::cout << "Circle: ";
  testShape(*circle);
  std::cout << "\nRectangle: ";
  testShape(*rectangle);

  shilov::CompositeShape compositeShape{};
  try
  {
    compositeShape.pushBack(circle);
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(std::make_shared<shilov::CompositeShape>());
  }
  catch (const std::exception& error)
  {
    std::cerr << "\n" << error.what() << "\n";
    return 1;
  }
  std::cout << "\nCompositeShape: Size: " << compositeShape.size() << "\n";
  testShape(compositeShape);

  std::cout << "\nShapeMatrix\n";
  shilov::ShapeMatrix shapeMatrix;
  try
  {
    shilov::CompositeShape tempCompositeShape;
    tempCompositeShape.pushBack(std::make_shared<shilov::Rectangle>(3, 6, 6, 7));
    tempCompositeShape.pushBack(std::make_shared<shilov::Rectangle>(20, 32, 3, 4));
    tempCompositeShape.pushBack(std::make_shared<shilov::Circle>(3, 4, 5));
    shapeMatrix = partition(tempCompositeShape);
  }
  catch (const std::exception& error)
  {
    std::cerr << "\n" << error.what() << "\n";
    return 1;
  }
  printMatrixComponentsFrameRects(shapeMatrix);
  try
  {
    for (size_t i = 0; i < shapeMatrix.getLines(); ++i)
    {
      for (size_t j = 0; j < shapeMatrix.getColumns(); ++j)
      {
        std::shared_ptr<shilov::Shape>& shape = shapeMatrix.cell(i, j);
        if (shape != nullptr)
        {
          shape->scale(6);
        }
      }
    }
    redistribution(shapeMatrix);
  }
  catch (const std::exception& error)
  {
    std::cerr << "\n" << error.what() << "\n";
    return 1;
  }
  std::cout << "ShapeMatrix after change figures and redistribution\n";
  printMatrixComponentsFrameRects(shapeMatrix);

  return 0;
}

inline void testShape(shilov::Shape& shape)
{
  std::cout << "Area: " << shape.getArea() << " | ";
  try
  {
    shape.scale(6);
    std::cout << "Area after scale: " << shape.getArea() << " | ";
  }
  catch (const std::exception& error)
  {
    std::cerr << "\n" << error.what() << ", scaling not done\n";
  }
  shape.move({7, 8});
  std::cout << "MoveTo Point: (" << shape.getPosition().x << ", " << shape.getPosition().y << ") | ";
  shape.move(3, 2);
  std::cout << "MoveBy Point: (" << shape.getPosition().x << ", " << shape.getPosition().y << ") | ";
  shilov::rectangle_t frameRect = shape.getFrameRect();
  std::cout << "The rectangle that frame the shape has parameters: Height: " << frameRect.height << "; Width: "
    << frameRect.width << "; Point: (" << frameRect.pos.x << ", " << frameRect.pos.y << ")\n";
  shape.rotate(145);
  frameRect = shape.getFrameRect();
  std::cout << "Frame rect parameters after rotate: Height: " << frameRect.height << "; Width: "
    << frameRect.width << "; Point: (" << frameRect.pos.x << ", " << frameRect.pos.y << ")\n";
}

inline void printMatrixComponentsFrameRects(shilov::ShapeMatrix& shapeMatrix)
{
  for (size_t i = 0; i < shapeMatrix.getLines(); ++i)
  {
    for (size_t j = 0; j < shapeMatrix.getColumns(); ++j)
    {
      std::shared_ptr<shilov::Shape>& shape = shapeMatrix.cell(i, j);
      if (shape != nullptr)
      {
        shilov::rectangle_t frameRect = shape->getFrameRect();
        std::cout << "Layer, number: " << i << ", " << j
          << " The rectangle that frame the shape has parameters: Height: " << frameRect.height << "; Width: "
          << frameRect.width << "; Point: (" << frameRect.pos.x << ", " << frameRect.pos.y << ")\n";
      }
    }
  }
}
