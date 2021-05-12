#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(TestRectangle, *boost::unit_test::tolerance(0.0001))

  BOOST_AUTO_TEST_CASE(TestCorrectConstructor1)
  {
    BOOST_CHECK_NO_THROW(shilov::Rectangle(1, 2, 3, 4));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectConstructor2)
  {
    BOOST_CHECK_NO_THROW(shilov::Rectangle(-1, 2, 3, 4));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectConstructor3)
  {
    BOOST_CHECK_NO_THROW(shilov::Rectangle(1, -2, 3, 4));
  }

  BOOST_AUTO_TEST_CASE(TestConstructorWithNegativeWidth)
  {
    BOOST_CHECK_THROW(shilov::Rectangle(1, 2, -3, 4), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestConstructorWithNegativeHeight)
  {
    BOOST_CHECK_THROW(shilov::Rectangle(1, 2, 3, -4), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestConstructorWithZeroWidth)
  {
    BOOST_CHECK_THROW(shilov::Rectangle(1, 2, 0, 4), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestConstructorWithZeroHeight)
  {
    BOOST_CHECK_THROW(shilov::Rectangle(1, 2, 3, 0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestCorrectConstructorWithRectangleT1)
  {
    BOOST_CHECK_NO_THROW(shilov::Rectangle({{1, 2}, 3, 4}));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectConstructorWithRectangleT2)
  {
    BOOST_CHECK_NO_THROW(shilov::Rectangle({{-1, 2}, 3, 4}));
  }

  BOOST_AUTO_TEST_CASE(TestCorrectConstructorWithRectangleT3)
  {
    BOOST_CHECK_NO_THROW(shilov::Rectangle({{1, -2}, 3, 4}));
  }

  BOOST_AUTO_TEST_CASE(TestConstructorRectangleTWithNegativeWidth)
  {
    BOOST_CHECK_THROW(shilov::Rectangle({{1, 2}, -3, 4}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestConstructorRectangleTWithNegativeHeight)
  {
    BOOST_CHECK_THROW(shilov::Rectangle({{1, 2}, 3, -4}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestConstructorRectangleTWithZeroWidth)
  {
    BOOST_CHECK_THROW(shilov::Rectangle({{1, 2}, 0, 4}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestConstructorRectangleTWithZeroHeight)
  {
    BOOST_CHECK_THROW(shilov::Rectangle({{1, 2}, 3, 0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestMoveTo)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    shilov::point_t expectedPoint = {4, 5};

    rectangle.move(expectedPoint);

    BOOST_TEST(rectangle.getPosition().x == expectedPoint.x);
    BOOST_TEST(rectangle.getPosition().y == expectedPoint.y);
  }

  BOOST_AUTO_TEST_CASE(TestMoveBy)
  {
    double dx = 5;
    double dy = 6;
    shilov::Rectangle rectangle(1, 2, 3, 4);
    shilov::point_t expectedPoint = {rectangle.getPosition().x + dx, rectangle.getPosition().y + dy};

    rectangle.move(dx, dy);

    BOOST_TEST(rectangle.getPosition().x == expectedPoint.x);
    BOOST_TEST(rectangle.getPosition().y == expectedPoint.y);
  }

  BOOST_AUTO_TEST_CASE(TestGetPosition)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);

    BOOST_TEST(rectangle.getPosition().x == 1);
    BOOST_TEST(rectangle.getPosition().y == 2);
  }

  BOOST_AUTO_TEST_CASE(TestGetWidth)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);

    BOOST_TEST(rectangle.getWidth() == 3);
  }

  BOOST_AUTO_TEST_CASE(TestGetHeight)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);

    BOOST_TEST(rectangle.getHeight() == 4);
  }

  BOOST_AUTO_TEST_CASE(TestGetArea)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double expectedArea = 3 * 4;

    double area = rectangle.getArea();

    BOOST_TEST(area == expectedArea);
  }

  BOOST_AUTO_TEST_CASE(TestGetFrameRectWithoutRotate)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);

    shilov::rectangle_t frameRect = rectangle.getFrameRect();

    BOOST_TEST(rectangle.getWidth() == frameRect.width);
    BOOST_TEST(rectangle.getHeight() == frameRect.height);
    BOOST_TEST(rectangle.getPosition().x == frameRect.pos.x);
    BOOST_TEST(rectangle.getPosition().y == frameRect.pos.y);
  }

  BOOST_AUTO_TEST_CASE(TestGetFrameRectWithRotate)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    shilov::rectangle_t expectedFrameRect{{1, 2}, 4.9641, 4.59808};
    rectangle.rotate(120);

    shilov::rectangle_t frameRect = rectangle.getFrameRect();

    BOOST_TEST(frameRect.width == expectedFrameRect.width);
    BOOST_TEST(frameRect.height == expectedFrameRect.height);
    BOOST_TEST(frameRect.pos.x == expectedFrameRect.pos.x);
    BOOST_TEST(frameRect.pos.y == expectedFrameRect.pos.y);
  }

  BOOST_AUTO_TEST_CASE(TestSetWidth)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double expectedWidth = 5;

    BOOST_CHECK_NO_THROW(rectangle.setWidth(expectedWidth));

    BOOST_TEST(rectangle.getWidth() == expectedWidth);
    BOOST_TEST(rectangle.getHeight() == 4);
    BOOST_TEST(rectangle.getPosition().x == 1);
    BOOST_TEST(rectangle.getPosition().y == 2);
  }

  BOOST_AUTO_TEST_CASE(TestWrongSetWidth)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    BOOST_CHECK_THROW(rectangle.setWidth(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestSetHeight)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double expectedHeight = 5;

    BOOST_CHECK_NO_THROW(rectangle.setHeight(expectedHeight));

    BOOST_TEST(rectangle.getHeight() == expectedHeight);
    BOOST_TEST(rectangle.getWidth() == 3);
    BOOST_TEST(rectangle.getPosition().x == 1);
    BOOST_TEST(rectangle.getPosition().y == 2);
  }

  BOOST_AUTO_TEST_CASE(TestWrongSetHeight)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    BOOST_CHECK_THROW(rectangle.setHeight(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScale)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double expectedWidth = 3 * 5;
    double expectedHeight = 4 * 5;

    BOOST_CHECK_NO_THROW(rectangle.scale(5));

    BOOST_TEST(rectangle.getWidth() == expectedWidth);
    BOOST_TEST(rectangle.getHeight() == expectedHeight);
    BOOST_TEST(rectangle.getPosition().x == 1);
    BOOST_TEST(rectangle.getPosition().y == 2);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithZeroCoefficient)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    BOOST_CHECK_THROW(rectangle.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithNegativeCoefficient)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    BOOST_CHECK_THROW(rectangle.scale(-1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedWidthAfterMoveTo)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double widthBeforeMove = rectangle.getWidth();

    rectangle.move({7, 8});
    double widthAfterMove = rectangle.getWidth();

    BOOST_TEST(widthAfterMove == widthBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedHeightAfterMoveTo)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double heightBeforeMove = rectangle.getHeight();

    rectangle.move({7, 8});
    double heightAfterMove = rectangle.getHeight();

    BOOST_TEST(heightAfterMove == heightBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedWidthAfterMoveBy)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double widthBeforeMove = rectangle.getWidth();

    rectangle.move(3, 3);
    double widthAfterMove = rectangle.getWidth();

    BOOST_TEST(widthAfterMove == widthBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedHeightAfterMoveBy)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double heightBeforeMove = rectangle.getHeight();

    rectangle.move(3, 3);
    double heightAfterMove = rectangle.getHeight();

    BOOST_TEST(heightAfterMove == heightBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedFrameRectAfterMoveTo)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    shilov::rectangle_t frameRectBeforeMove = rectangle.getFrameRect();

    rectangle.move({7, 8});
    shilov::rectangle_t frameRectAfterMove = rectangle.getFrameRect();

    BOOST_TEST(frameRectBeforeMove.width == frameRectAfterMove.width);
    BOOST_TEST(frameRectBeforeMove.height == frameRectAfterMove.height);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedFrameRectAfterMoveBy)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    shilov::rectangle_t frameRectBeforeMove = rectangle.getFrameRect();

    rectangle.move(3, 3);
    shilov::rectangle_t frameRectAfterMove = rectangle.getFrameRect();

    BOOST_TEST(frameRectBeforeMove.width == frameRectAfterMove.width);
    BOOST_TEST(frameRectBeforeMove.height == frameRectAfterMove.height);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedAreaAfterMoveTo)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double areaBeforeMove = rectangle.getArea();

    rectangle.move({7, 8});
    double areaAfterMove = rectangle.getArea();

    BOOST_TEST(areaAfterMove == areaBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedAreaAfterMoveBy)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double areaBeforeMove = rectangle.getArea();

    rectangle.move(3, 3);
    double areaAfterMove = rectangle.getArea();

    BOOST_TEST(areaAfterMove == areaBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedRotationAngleAfterMoveBy)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double rotationAngleBeforeMove = rectangle.getRotationAngle();

    rectangle.move(3, 3);

    BOOST_TEST(rectangle.getRotationAngle() == rotationAngleBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedRotationAngleAfterMoveTo)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double rotationAngleBeforeMove = rectangle.getRotationAngle();

    rectangle.move({7, 8});

    BOOST_TEST(rectangle.getRotationAngle() == rotationAngleBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestChangedAreaAfterScale)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double scaleCoefficient = 6;
    double areaBeforeScale = rectangle.getArea();

    BOOST_CHECK_NO_THROW(rectangle.scale(scaleCoefficient));
    double areaAfterScale = rectangle.getArea();

    BOOST_TEST(areaAfterScale / areaBeforeScale == scaleCoefficient * scaleCoefficient);
  }

  BOOST_AUTO_TEST_CASE(TestGetRotationAngle)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);

    BOOST_TEST(rectangle.getRotationAngle() == 0);
  }

  BOOST_AUTO_TEST_CASE(TestRotate)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double firstAngle = 48;
    double secondAngle = 96;

    rectangle.rotate(firstAngle);
    rectangle.rotate(secondAngle);

    BOOST_TEST(rectangle.getRotationAngle() == firstAngle + secondAngle);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedPositionAfterRotate)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    shilov::point_t positionBeforeRotate = rectangle.getPosition();
    double angle = 48;

    rectangle.rotate(angle);

    BOOST_TEST(rectangle.getPosition().x == positionBeforeRotate.x);
    BOOST_TEST(rectangle.getPosition().y == positionBeforeRotate.y);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedWidthAndHeightAfterRotate)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double widthBeforeRotate = rectangle.getWidth();
    double heightBeforeRotate = rectangle.getHeight();
    double angle = 48;

    rectangle.rotate(angle);

    BOOST_TEST(widthBeforeRotate == rectangle.getWidth());
    BOOST_TEST(heightBeforeRotate == rectangle.getHeight());
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedAreaAfterRotate)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double areaBeforeRotate = rectangle.getArea();
    double angle = 48;

    rectangle.rotate(angle);

    BOOST_TEST(rectangle.getArea() == areaBeforeRotate);
  }

  BOOST_AUTO_TEST_CASE(TestSetRotationAngle)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double angle = 148;

    rectangle.setRotationAngle(angle);

    BOOST_TEST(rectangle.getRotationAngle() == angle);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedPositionAfterSetRotationAngle)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    shilov::point_t positionBeforeRotate = rectangle.getPosition();
    double angle = 48;

    rectangle.setRotationAngle(angle);

    BOOST_TEST(rectangle.getPosition().x == positionBeforeRotate.x);
    BOOST_TEST(rectangle.getPosition().y == positionBeforeRotate.y);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedWidthAndHeightAfterSetRotationAngle)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double widthBeforeRotate = rectangle.getWidth();
    double heightBeforeRotate = rectangle.getHeight();
    double angle = 48;

    rectangle.setRotationAngle(angle);

    BOOST_TEST(widthBeforeRotate == rectangle.getWidth());
    BOOST_TEST(heightBeforeRotate == rectangle.getHeight());
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedAreaAfterSetRotationAngle)
  {
    shilov::Rectangle rectangle(1, 2, 3, 4);
    double areaBeforeRotate = rectangle.getArea();
    double angle = 48;

    rectangle.setRotationAngle(angle);

    BOOST_TEST(rectangle.getArea() == areaBeforeRotate);
  }

BOOST_AUTO_TEST_SUITE_END()
