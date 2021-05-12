#include <stdexcept>
#include <memory>
#include <limits>
#include <cmath>

#include <boost/test/unit_test.hpp>

#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace shilov;

const double WIDTH = 3;
const double HEIGHT = 4;
const double RADIUS = 5;

const double X1 = 13.2;
const double X2 = 4.1;
const double X3 = 15;
const double Y1 = 16;
const double Y2 = 7.1;
const double Y3 = 18.2;

const double COEFFICIENT = 6;
const double ANGLE = -145;

inline void testRectanglesEqual(const rectangle_t& rect1, const rectangle_t& rect2)
{
  BOOST_TEST(rect1.width == rect2.width);
  BOOST_TEST(rect1.height == rect2.height);
}

inline void testPositionsEqual(const point_t& point1, const point_t& point2)
{
  BOOST_TEST(point1.x == point2.x);
  BOOST_TEST(point1.y == point2.y);
}

inline void initialCompositeShape(CompositeShape& compositeShape)
{
  std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(X1, Y1, WIDTH, HEIGHT);
  std::shared_ptr<Circle> circle = std::make_shared<Circle>(X2, Y2, RADIUS);
  compositeShape.pushBack(rectangle);
  compositeShape.pushBack(circle);
}

BOOST_AUTO_TEST_SUITE(TestCompositeShape, *boost::unit_test::tolerance(0.0001))

  BOOST_AUTO_TEST_CASE(TestCopyConstructor)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);

    CompositeShape secondCompositeShape(originalCompositeShape);

    BOOST_TEST(originalCompositeShape[0] == secondCompositeShape[0]);
    BOOST_TEST(originalCompositeShape[1] == secondCompositeShape[1]);
    BOOST_TEST(originalCompositeShape.size() == secondCompositeShape.size());
  }

  BOOST_AUTO_TEST_CASE(TestCopyAssignmentOperator)
  {
    CompositeShape originalCompositeShape{};
    CompositeShape secondCompositeShape{};
    initialCompositeShape(originalCompositeShape);

    secondCompositeShape = originalCompositeShape;

    BOOST_TEST(originalCompositeShape[0] == secondCompositeShape[0]);
    BOOST_TEST(originalCompositeShape[1] == secondCompositeShape[1]);
    BOOST_TEST(originalCompositeShape.size() == secondCompositeShape.size());
  }

  BOOST_AUTO_TEST_CASE(TestIndexingOperator)
  {
    CompositeShape originalCompositeShape{};
    std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(X1, Y1, WIDTH, HEIGHT);
    std::shared_ptr<Circle> circle = std::make_shared<Circle>(X2, Y2, RADIUS);
    originalCompositeShape.pushBack(rectangle);
    originalCompositeShape.pushBack(circle);

    BOOST_TEST(originalCompositeShape[0] == rectangle);
    BOOST_TEST(originalCompositeShape[1] == circle);
  }

  BOOST_AUTO_TEST_CASE(TestOutOfRangeIndexingOperator)
  {
    CompositeShape originalCompositeShape{};
    std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(X1, Y1, WIDTH, HEIGHT);
    originalCompositeShape.pushBack(rectangle);

    BOOST_CHECK_THROW(originalCompositeShape[1], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(TestIndexingOperatorEmptyCompositeShape)
  {
    CompositeShape originalCompositeShape{};

    BOOST_CHECK_THROW(originalCompositeShape[0], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(TestMoveTo)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);

    BOOST_CHECK_NO_THROW(originalCompositeShape.move({X3, Y3}));

    testPositionsEqual(originalCompositeShape.getPosition(), {X3, Y3});
  }

  BOOST_AUTO_TEST_CASE(TestMoveBy)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);
    point_t positionBeforeMove = originalCompositeShape.getPosition();
    point_t expectedPointAfterMove = {positionBeforeMove.x + X3, positionBeforeMove.y + Y3};

    BOOST_CHECK_NO_THROW(originalCompositeShape.move(X3, Y3));

    testPositionsEqual(originalCompositeShape.getPosition(), expectedPointAfterMove);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedFrameRectAfterMoveTo)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);
    rectangle_t frameRectBeforeMove = originalCompositeShape.getFrameRect();

    BOOST_CHECK_NO_THROW(originalCompositeShape.move({X3, Y3}));

    testRectanglesEqual(frameRectBeforeMove, originalCompositeShape.getFrameRect());
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedFrameRectAfterMoveBy)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);
    rectangle_t frameRectBeforeMove = originalCompositeShape.getFrameRect();

    BOOST_CHECK_NO_THROW(originalCompositeShape.move(X3, Y3));

    testRectanglesEqual(frameRectBeforeMove, originalCompositeShape.getFrameRect());
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedAreaAfterMoveTo)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);
    double areaBeforeMove = originalCompositeShape.getArea();

    BOOST_CHECK_NO_THROW(originalCompositeShape.move({X3, Y3}));

    BOOST_TEST(areaBeforeMove == originalCompositeShape.getArea());
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedAreaAfterMoveBy)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);
    double areaBeforeMove = originalCompositeShape.getArea();

    BOOST_CHECK_NO_THROW(originalCompositeShape.move(X3, Y3));

    BOOST_TEST(areaBeforeMove == originalCompositeShape.getArea());
  }

  BOOST_AUTO_TEST_CASE(TestGetPositionThroughCalculation)
  {
    CompositeShape originalCompositeShape{};
    std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(12, 2, 3, 4);
    std::shared_ptr<Circle> circle = std::make_shared<Circle>(3, 4, 5);
    originalCompositeShape.pushBack(rectangle);
    originalCompositeShape.pushBack(circle);
    point_t expectedPosition = {5.75, 4};

    testPositionsEqual(expectedPosition, originalCompositeShape.getPosition());
  }

  BOOST_AUTO_TEST_CASE(TestGetPositionThroughGetFrameRect)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);

    testPositionsEqual(originalCompositeShape.getFrameRect().pos, originalCompositeShape.getPosition());
  }

  BOOST_AUTO_TEST_CASE(TestGetArea)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);
    double expectedArea = 0;
    for (size_t i = 0; i < originalCompositeShape.size(); ++i)
    {
      expectedArea += originalCompositeShape[i]->getArea();
    }

    BOOST_TEST(expectedArea == originalCompositeShape.getArea());
  }

  BOOST_AUTO_TEST_CASE(TestGetFrameRect)
  {
    CompositeShape originalCompositeShape{};
    std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(12, 2, 3, 4);
    std::shared_ptr<Circle> circle = std::make_shared<Circle>(3, 4, 5);
    originalCompositeShape.pushBack(rectangle);
    originalCompositeShape.pushBack(circle);
    rectangle_t expectedFrameRect = {{5.75, 4}, 15.5, 10};

    testRectanglesEqual(expectedFrameRect, originalCompositeShape.getFrameRect());
    testPositionsEqual(expectedFrameRect.pos, originalCompositeShape.getFrameRect().pos);
  }

  BOOST_AUTO_TEST_CASE(TestScale)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);
    rectangle_t expectedFrameRect = {originalCompositeShape.getPosition(),
      originalCompositeShape.getFrameRect().width * COEFFICIENT,
      originalCompositeShape.getFrameRect().height * COEFFICIENT};

    BOOST_CHECK_NO_THROW(originalCompositeShape.scale(COEFFICIENT));

    testRectanglesEqual(expectedFrameRect, originalCompositeShape.getFrameRect());
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithZeroCoefficient)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);

    BOOST_CHECK_THROW(originalCompositeShape.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithNegativeCoefficient)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);

    BOOST_CHECK_THROW(originalCompositeShape.scale(-COEFFICIENT), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedPositionAfterScale)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);
    point_t positionBeforeScale = originalCompositeShape.getPosition();

    originalCompositeShape.scale(COEFFICIENT);
    point_t positionAfterScale = originalCompositeShape.getPosition();

    testPositionsEqual(positionBeforeScale, positionAfterScale);
  }

  BOOST_AUTO_TEST_CASE(TestChangedAreaAfterScale)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);
    double areaBeforeScale = originalCompositeShape.getArea();

    originalCompositeShape.scale(COEFFICIENT);
    double areaAfterScale = originalCompositeShape.getArea();

    BOOST_TEST(areaBeforeScale * COEFFICIENT * COEFFICIENT == areaAfterScale);
  }

  BOOST_AUTO_TEST_CASE(TestPushBack)
  {
    CompositeShape originalCompositeShape{};
    std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(X1, Y1, WIDTH, HEIGHT);
    std::shared_ptr<Circle> circle = std::make_shared<Circle>(X2, Y2, RADIUS);
    size_t sizeBeforePushBack = originalCompositeShape.size();

    originalCompositeShape.pushBack(rectangle);
    originalCompositeShape.pushBack(circle);

    BOOST_TEST(originalCompositeShape[0] == rectangle);
    BOOST_TEST(originalCompositeShape[1] == circle);
    BOOST_TEST(sizeBeforePushBack + 2 == originalCompositeShape.size());
  }

  BOOST_AUTO_TEST_CASE(TestPushBackWithAddToItself)
  {
    std::shared_ptr<CompositeShape> originalCompositeShape{};

    BOOST_CHECK_THROW(originalCompositeShape->pushBack(originalCompositeShape), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestPushBackWithNullPointer)
  {
    CompositeShape originalCompositeShape{};

    BOOST_CHECK_THROW(originalCompositeShape.pushBack(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestPopBack)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);
    size_t sizeBeforePopBack = originalCompositeShape.size();

    originalCompositeShape.popBack();

    BOOST_TEST(sizeBeforePopBack == originalCompositeShape.size() + 1);
  }

  BOOST_AUTO_TEST_CASE(TestPopBackEmptyCompositeShape)
  {
    CompositeShape originalCompositeShape{};
    BOOST_CHECK_THROW(originalCompositeShape.popBack(), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(TestIsEmpty)
  {
    CompositeShape emptyCompositeShape{};
    CompositeShape notEmptyCompositeShape{};
    initialCompositeShape(notEmptyCompositeShape);

    BOOST_TEST(emptyCompositeShape.isEmpty());
    BOOST_TEST(!notEmptyCompositeShape.isEmpty());
  }

  BOOST_AUTO_TEST_CASE(TestSize)
  {
    CompositeShape originalCompositeShape{};
    std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(X1, Y1, WIDTH, HEIGHT);
    std::shared_ptr<Circle> circle = std::make_shared<Circle>(X2, Y2, RADIUS);
    originalCompositeShape.pushBack(rectangle);
    originalCompositeShape.pushBack(circle);
    double expectedSize = 2;

    BOOST_TEST(originalCompositeShape.size() == expectedSize);
  }

  BOOST_AUTO_TEST_CASE(TestMoveToEmptyCompositeShape)
  {
    CompositeShape originalCompositeShape{};

    BOOST_CHECK_NO_THROW(originalCompositeShape.move({X3, Y3}));

    BOOST_CHECK(std::isnan(originalCompositeShape.getPosition().x));
    BOOST_CHECK(std::isnan(originalCompositeShape.getPosition().y));
  }

  BOOST_AUTO_TEST_CASE(TestMoveByEmptyCompositeShape)
  {
    CompositeShape originalCompositeShape{};

    BOOST_CHECK_NO_THROW(originalCompositeShape.move(X3, Y3));

    BOOST_CHECK(std::isnan(originalCompositeShape.getPosition().x));
    BOOST_CHECK(std::isnan(originalCompositeShape.getPosition().y));
  }

  BOOST_AUTO_TEST_CASE(TestGetAreaEmptyCompositeShape)
  {
    CompositeShape originalCompositeShape{};

    BOOST_TEST(originalCompositeShape.getArea() == 0);
  }

  BOOST_AUTO_TEST_CASE(TestGetFrameRectEmptyCompositeShape)
  {
    CompositeShape originalCompositeShape{};

    BOOST_CHECK(std::isnan(originalCompositeShape.getFrameRect().width));
    BOOST_CHECK(std::isnan(originalCompositeShape.getFrameRect().height));
    BOOST_CHECK(std::isnan(originalCompositeShape.getFrameRect().pos.x));
    BOOST_CHECK(std::isnan(originalCompositeShape.getFrameRect().pos.y));
  }

  BOOST_AUTO_TEST_CASE(TestScaleEmptyCompositeShape)
  {
    CompositeShape originalCompositeShape{};

    originalCompositeShape.scale(COEFFICIENT);

    BOOST_CHECK(std::isnan(originalCompositeShape.getFrameRect().width));
    BOOST_CHECK(std::isnan(originalCompositeShape.getFrameRect().height));
    BOOST_CHECK(std::isnan(originalCompositeShape.getFrameRect().pos.x));
    BOOST_CHECK(std::isnan(originalCompositeShape.getFrameRect().pos.y));
  }

  BOOST_AUTO_TEST_CASE(TestRotate)
  {
    CompositeShape originalCompositeShape{};
    std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(13.2, 16, 3, 4);
    std::shared_ptr<Circle> circle = std::make_shared<Circle>(4.1, 7.1, 5);
    originalCompositeShape.pushBack(rectangle);
    originalCompositeShape.pushBack(circle);
    rectangle_t expectedFrameRect{{7.50158, 9.06818}, 10, 20.0087};

    originalCompositeShape.rotate(-145);

    testRectanglesEqual(expectedFrameRect, originalCompositeShape.getFrameRect());
    testPositionsEqual(expectedFrameRect.pos, originalCompositeShape.getFrameRect().pos);
  }

  BOOST_AUTO_TEST_CASE(TestNotChangedAreaAfterRotate)
  {
    CompositeShape originalCompositeShape{};
    initialCompositeShape(originalCompositeShape);
    double areaBeforeRotate = originalCompositeShape.getArea();

    originalCompositeShape.rotate(ANGLE);

    BOOST_TEST(areaBeforeRotate == originalCompositeShape.getArea());
  }

BOOST_AUTO_TEST_SUITE_END()
