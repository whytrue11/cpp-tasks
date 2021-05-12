#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(TestCircle, *boost::unit_test::tolerance(0.0001))

  BOOST_AUTO_TEST_CASE(TestCorrectConstructor1)
  {
    BOOST_CHECK_NO_THROW(shilov::Circle(1, 2, 3));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectConstructor2)
  {
    BOOST_CHECK_NO_THROW(shilov::Circle(-1, 2, 3));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectConstructor3)
  {
    BOOST_CHECK_NO_THROW(shilov::Circle(1, -2, 3));
  }

  BOOST_AUTO_TEST_CASE(TestConstructorWithNegativeRadius)
  {
    BOOST_CHECK_THROW(shilov::Circle(1, 2, -3), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestConstructorWithZeroRadius)
  {
    BOOST_CHECK_THROW(shilov::Circle(1, 2, 0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestMoveTo)
  {
    shilov::Circle circle(1, 2, 3);
    shilov::point_t expectedPoint = {4, 5};

    circle.move(expectedPoint);

    BOOST_TEST(circle.getPosition().x == expectedPoint.x);
    BOOST_TEST(circle.getPosition().y == expectedPoint.y);
  }

  BOOST_AUTO_TEST_CASE(TestMoveBy)
  {
    double dx = 5;
    double dy = 6;
    shilov::Circle circle(1, 2, 3);
    shilov::point_t expectedPoint = {circle.getPosition().x + dx, circle.getPosition().y + dy};

    circle.move(dx, dy);

    BOOST_TEST(circle.getPosition().x == expectedPoint.x);
    BOOST_TEST(circle.getPosition().y == expectedPoint.y);
  }

  BOOST_AUTO_TEST_CASE(TestGetPosition)
  {
    shilov::Circle circle(1, 2, 3);

    BOOST_TEST(circle.getPosition().x == 1);
    BOOST_TEST(circle.getPosition().y == 2);
  }

  BOOST_AUTO_TEST_CASE(TestGetRadius)
  {
    shilov::Circle circle(1, 2, 3);

    BOOST_TEST(circle.getRadius() == 3);
  }

  BOOST_AUTO_TEST_CASE(TestGetArea)
  {
    shilov::Circle circle(1, 2, 3);
    double expectedArea = M_PI * 3 * 3;

    double area = circle.getArea();

    BOOST_TEST(area == expectedArea);
  }

  BOOST_AUTO_TEST_CASE(TestGetFrameRect)
  {
    shilov::Circle circle(1, 2, 3);
    double expectedHeightAndWidth = circle.getRadius() * 2;

    shilov::rectangle_t frameRect = circle.getFrameRect();

    BOOST_TEST(expectedHeightAndWidth == frameRect.height);
    BOOST_TEST(expectedHeightAndWidth == frameRect.width);
    BOOST_TEST(frameRect.pos.x == 1);
    BOOST_TEST(frameRect.pos.y == 2);
  }

  BOOST_AUTO_TEST_CASE(TestSetRadius)
  {
    shilov::Circle circle(1, 2, 3);
    double expectedRadius = 5;

    BOOST_CHECK_NO_THROW(circle.setRadius(expectedRadius));

    BOOST_TEST(circle.getRadius() == expectedRadius);
    BOOST_TEST(circle.getPosition().x == 1);
    BOOST_TEST(circle.getPosition().y == 2);
  }

  BOOST_AUTO_TEST_CASE(TestWrongSetRadius)
  {
    shilov::Circle circle(1, 2, 3);
    BOOST_CHECK_THROW(circle.setRadius(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScale)
  {
    shilov::Circle circle(1, 2, 3);
    double expectedRadius = 3 * 4;

    BOOST_CHECK_NO_THROW(circle.scale(4));

    BOOST_TEST(circle.getRadius() == expectedRadius);
    BOOST_TEST(circle.getPosition().x == 1);
    BOOST_TEST(circle.getPosition().y == 2);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithZeroCoefficient)
  {
    shilov::Circle circle(1, 2, 3);
    BOOST_CHECK_THROW(circle.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithNegativeCoefficient)
  {
    shilov::Circle circle(1, 2, 3);
    BOOST_CHECK_THROW(circle.scale(-1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedRadiusAfterMoveTo)
  {
    shilov::Circle circle(1, 2, 3);
    double radiusBeforeMove = circle.getRadius();

    circle.move({7, 8});
    double radiusAfterMove = circle.getRadius();

    BOOST_TEST(radiusAfterMove == radiusBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedRadiusAfterMoveBy)
  {
    shilov::Circle circle(1, 2, 3);
    double radiusBeforeMove = circle.getRadius();

    circle.move(3, 3);
    double radiusAfterMove = circle.getRadius();

    BOOST_TEST(radiusAfterMove == radiusBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedFrameRectAfterMoveTo)
  {
    shilov::Circle circle(1, 2, 3);
    shilov::rectangle_t frameRectBeforeMove = circle.getFrameRect();

    circle.move({7, 8});
    shilov::rectangle_t frameRectAfterMove = circle.getFrameRect();

    BOOST_TEST(frameRectBeforeMove.width == frameRectAfterMove.width);
    BOOST_TEST(frameRectBeforeMove.height == frameRectAfterMove.height);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedFrameRectAfterMoveBy)
  {
    shilov::Circle circle(1, 2, 3);
    shilov::rectangle_t frameRectBeforeMove = circle.getFrameRect();

    circle.move(3, 3);
    shilov::rectangle_t frameRectAfterMove = circle.getFrameRect();

    BOOST_TEST(frameRectBeforeMove.width == frameRectAfterMove.width);
    BOOST_TEST(frameRectBeforeMove.height == frameRectAfterMove.height);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedAreaAfterMoveTo)
  {
    shilov::Circle circle(1, 2, 3);
    double areaBeforeMove = circle.getArea();

    circle.move({7, 8});
    double areaAfterMove = circle.getArea();

    BOOST_TEST(areaAfterMove == areaBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedAreaAfterMoveBy)
  {
    shilov::Circle circle(1, 2, 3);
    double areaBeforeMove = circle.getArea();

    circle.move(3, 3);
    double areaAfterMove = circle.getArea();

    BOOST_TEST(areaAfterMove == areaBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestChangedAreaAfterScale)
  {
    shilov::Circle circle(1, 2, 3);
    double scaleCoefficient = 5;
    double areaBeforeScale = circle.getArea();

    BOOST_CHECK_NO_THROW(circle.scale(scaleCoefficient));
    double areaAfterScale = circle.getArea();

    BOOST_TEST(areaAfterScale / areaBeforeScale == scaleCoefficient * scaleCoefficient);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedCircleAfterRotate)
  {
    shilov::Circle circle(1, 2, 3);
    shilov::Circle copyCircle(circle);

    circle.rotate(48);

    BOOST_TEST(circle.getRadius() == copyCircle.getRadius());
    BOOST_TEST(circle.getPosition().x == copyCircle.getPosition().x);
    BOOST_TEST(circle.getPosition().y == copyCircle.getPosition().y);
  }

BOOST_AUTO_TEST_SUITE_END()
