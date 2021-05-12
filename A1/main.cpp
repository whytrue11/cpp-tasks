#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  Circle* circle = nullptr;
  Shape* rectangle = nullptr;
  try
  {
    circle = new Circle(1, 1.5, 3);
    rectangle = new Rectangle(12, 18.3, 4, 20.5);
    std::cout << "Circle area with radius " << circle->getRadius() << ": " << circle->getArea()
              << " | ";
    std::cout << "Rectangle area: " << rectangle->getArea() << " | ";

    Rectangle rectCircle(circle->getFrameRect());
    std::cout << "The rectangle that frame the circle has parameters: Height: " << rectCircle.getHeight()
              << "; Width: " << rectCircle.getWidth() <<
              "; Point: (" << rectCircle.getPosition().x << ", " << rectCircle.getPosition().y << ")"
              << " | ";

    Rectangle rectRectangle(rectangle->getFrameRect());
    std::cout << "The rectangle that frame the rectangle has parameters: Height: " << rectRectangle.getHeight()
              << "; Width: " << rectRectangle.getWidth() <<
              "; Point: (" << rectRectangle.getPosition().x << ", " << rectRectangle.getPosition().y << ")"
              << " | ";

    rectRectangle.move(2, 3);
    std::cout << "Rectangle: " << "After move (dx, dy): Point: (" << rectRectangle.getPosition().x << ", "
              << rectRectangle.getPosition().y
              << ")" << " | ";

    rectRectangle.move({3, 3});
    std::cout << "After move in point: Point: (" << rectRectangle.getPosition().x << ", "
              << rectRectangle.getPosition().y
              << ")" << " | ";

    circle->move(2, 3);
    std::cout << "Circle: " << "After move (dx, dy): Point: (" << circle->getPosition().x << ", "
              << circle->getPosition().y
              << ")" << " | ";

    circle->move({5.7, 5.6});
    std::cout << "After move in point: Point: (" << circle->getPosition().x << ", "
              << circle->getPosition().y
              << ")";
  }
  catch (const std::exception& error)
  {
    delete circle;
    delete rectangle;
    std::cerr << error.what();
    return 1;
  }
  delete circle;
  delete rectangle;
  return 0;
}
