#include <iostream>
#include <memory>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace shilov;

inline void testShape(Shape& shape)
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
  Rectangle frameRect(shape.getFrameRect());
  std::cout << "The rectangle that frame the shape has parameters: Height: " << frameRect.getHeight()
    << "; Width: " << frameRect.getWidth() <<
    "; Point: (" << frameRect.getPosition().x << ", " << frameRect.getPosition().y << ")";
}

inline void printComponentsPositions(CompositeShape& compositeShape)
{
  if (compositeShape.isEmpty())
  {
    std::cout << "Composite shape is empty\n";
  }
  else
  {
    std::cout << "Positions of the component shapes:\n";
    for (size_t i = 0; i < compositeShape.size(); ++i)
    {
      std::cout << i << ": Point (" << compositeShape[i]->getPosition().x << ", " << compositeShape[i]->getPosition().y
        << ")\n";
    }
  }
}

int main()
{
  std::shared_ptr<Circle> circle;
  std::shared_ptr<Shape> rectangle;
  try
  {
    circle = std::make_shared<Circle>(1, 1.5, 3);
    rectangle = std::make_shared<Rectangle>(12, 18.3, 4, 20.5);
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

  CompositeShape compositeShape{};
  circle->move({1, 4});
  rectangle->move({14, 6});
  try
  {
    compositeShape.pushBack(circle);
    compositeShape.pushBack(rectangle);
    compositeShape.pushBack(std::make_shared<CompositeShape>());
  }
  catch (const std::exception& error)
  {
    std::cerr << "\n" << error.what() << "\n";
    return 1;
  }

  std::cout << "\n\nCompositeShape: " << "Size: " << compositeShape.size() << " | Area: " << compositeShape.getArea()
    << " | ";
  try
  {
    compositeShape.scale(5);
    std::cout << "Area after scale: " << compositeShape.getArea() << "\n";
  }
  catch (const std::exception& error)
  {
    std::cerr << "\n" << error.what() << ", scaling not done\n";
  }
  compositeShape.move(3, 2);
  std::cout << "MoveBy Point: (" << compositeShape.getPosition().x << ", " << compositeShape.getPosition().y << ")\n";
  printComponentsPositions(compositeShape);

  compositeShape.move({7, 8});
  std::cout << "MoveTo Point: (" << compositeShape.getPosition().x << ", " << compositeShape.getPosition().y << ")\n";
  printComponentsPositions(compositeShape);

  try
  {
    Rectangle frameRect(compositeShape.getFrameRect());
    std::cout << "The rectangle that frame the composite shape has parameters: Height: " << frameRect.getHeight()
      << "; Width: " << frameRect.getWidth() <<
      "; Point: (" << frameRect.getPosition().x << ", " << frameRect.getPosition().y << ")";
  }
  catch (const std::exception& error)
  {
    std::cerr << "\n" << error.what();
  }

  return 0;
}
