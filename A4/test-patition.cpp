#include <stdexcept>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "partition.hpp"
#include "shape-matrix.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace shilov;

const double WIDTH1 = 6;
const double WIDTH2 = 3;
const double HEIGHT1 = 6;
const double HEIGHT2 = 4;
const double RADIUS = 5;

const double X1 = 3;
const double X2 = 20;
const double X3 = 3;
const double Y1 = 6;
const double Y2 = 32;
const double Y3 = 4;

BOOST_AUTO_TEST_SUITE(TestPartition)

  BOOST_AUTO_TEST_CASE(TestPartition)
  {
    std::shared_ptr<CompositeShape> compositeShape = std::make_shared<CompositeShape>();
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(X1, Y1, WIDTH1, HEIGHT1);
    std::shared_ptr<Shape> rectangle2 = std::make_shared<Rectangle>(X2, Y2, WIDTH2, HEIGHT2);
    std::shared_ptr<Shape> circle = std::make_shared<Circle>(X3, Y3, RADIUS);
    compositeShape->pushBack(rectangle1);
    compositeShape->pushBack(rectangle2);
    compositeShape->pushBack(circle);

    ShapeMatrix shapeMatrix = partition(*compositeShape);

    BOOST_TEST(shapeMatrix.getLines() == 2);
    BOOST_TEST(shapeMatrix.getColumns() == 2);
    BOOST_TEST(shapeMatrix.cell(0, 0) == rectangle1);
    BOOST_TEST(shapeMatrix.cell(0, 1) == rectangle2);
    BOOST_TEST(shapeMatrix.cell(1, 0) == circle);
  }

  BOOST_AUTO_TEST_CASE(TestPartitionEmptyCompositeShape)
  {
    CompositeShape compositeShape;
    BOOST_CHECK_NO_THROW(partition(compositeShape));
  }

  BOOST_AUTO_TEST_CASE(TestRedistribution)
  {
    std::shared_ptr<CompositeShape> compositeShape = std::make_shared<CompositeShape>();
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(X1, Y1, WIDTH1, HEIGHT1);
    std::shared_ptr<Shape> rectangle2 = std::make_shared<Rectangle>(X2, Y2, WIDTH2, HEIGHT2);
    std::shared_ptr<Shape> circle = std::make_shared<Circle>(X3, Y3, RADIUS);
    compositeShape->pushBack(rectangle1);
    compositeShape->pushBack(rectangle2);
    compositeShape->pushBack(circle);
    ShapeMatrix shapeMatrix = partition(*compositeShape);
    double linesBeforeRedistribution = shapeMatrix.getLines();
    double countBeforeRedistribution = shapeMatrix.getColumns();

    shapeMatrix.cell(0, 0).reset();
    redistribution(shapeMatrix);

    BOOST_TEST(shapeMatrix.getLines() != linesBeforeRedistribution);
    BOOST_TEST(shapeMatrix.getColumns() == countBeforeRedistribution);
    BOOST_TEST(shapeMatrix.cell(0, 0) == rectangle2);
    BOOST_TEST(shapeMatrix.cell(0, 1) == circle);
  }

  BOOST_AUTO_TEST_CASE(TestRedistributionEmptyShapeMatrix)
  {
    ShapeMatrix shapeMatrix{};
    BOOST_CHECK_NO_THROW(redistribution(shapeMatrix));
  }

BOOST_AUTO_TEST_SUITE_END()
