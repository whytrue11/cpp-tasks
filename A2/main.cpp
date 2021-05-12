#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

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

int main()
{
  Circle* circle = nullptr;
  Shape* rectangle = nullptr;
  try
  {
    circle = new Circle(1, 1.5, 3);
    rectangle = new Rectangle(12, 18.3, 4, 20.5);
  }
  catch (const std::exception& error)
  {
    delete circle;
    delete rectangle;
    std::cerr << error.what();
    return 1;
  }
  std::cout << "Circle: ";
  testShape(*circle);
  std::cout << "\nRectangle: ";
  testShape(*rectangle);

  delete circle;
  delete rectangle;
  return 0;
}
