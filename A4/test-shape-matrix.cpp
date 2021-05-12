#include <stdexcept>
#include <memory>

#include <boost/test/unit_test.hpp>

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

BOOST_AUTO_TEST_SUITE(TestShapeMatrix, *boost::unit_test::tolerance(0.0001))

  BOOST_AUTO_TEST_CASE(TestConstructorWithZeroColumnsParametr)
  {
    BOOST_CHECK_THROW(ShapeMatrix shapeMatrix(1, 0), std::logic_error);
  }

  BOOST_AUTO_TEST_CASE(TestConstructorWithZeroLinesParametr)
  {
    BOOST_CHECK_THROW(ShapeMatrix shapeMatrix(0, 3), std::logic_error);
  }

  BOOST_AUTO_TEST_CASE(TestGetLines)
  {
    ShapeMatrix shapeMatrix(1, 3);

    BOOST_TEST(shapeMatrix.getLines() == 1);
  }

  BOOST_AUTO_TEST_CASE(TestGetCount)
  {
    ShapeMatrix shapeMatrix(1, 3);

    BOOST_TEST(shapeMatrix.getColumns() == 3);
  }

  BOOST_AUTO_TEST_CASE(TestCell)
  {
    ShapeMatrix shapeMatrix(1, 1);
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(X1, Y1, WIDTH1, HEIGHT1);
    shapeMatrix.cell(0, 0) = rectangle1;

    BOOST_TEST(shapeMatrix.cell(0, 0) == rectangle1);
  }

  BOOST_AUTO_TEST_CASE(TestCellOutOfRange)
  {
    ShapeMatrix shapeMatrix{};

    BOOST_CHECK_THROW(shapeMatrix.cell(0, 0), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(TestResize)
  {
    ShapeMatrix shapeMatrix(1, 3);
    std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(X1, Y1, WIDTH1, HEIGHT1);
    std::shared_ptr<Shape> rectangle2 = std::make_shared<Rectangle>(X2, Y2, WIDTH2, HEIGHT2);
    std::shared_ptr<Shape> circle = std::make_shared<Circle>(X3, Y3, RADIUS);
    shapeMatrix.cell(0, 0) = rectangle1;
    shapeMatrix.cell(0, 1) = rectangle2;
    shapeMatrix.cell(0, 2) = circle;

    shapeMatrix.resize(3, 4);

    BOOST_TEST(shapeMatrix.getLines() == 3);
    BOOST_TEST(shapeMatrix.getColumns() == 4);
    BOOST_TEST(shapeMatrix.cell(0, 0) == rectangle1);
    BOOST_TEST(shapeMatrix.cell(0, 1) == rectangle2);
    BOOST_TEST(shapeMatrix.cell(0, 2) == circle);
  }

  BOOST_AUTO_TEST_CASE(TestResizeEqual)
  {
    ShapeMatrix shapeMatrix{};

    BOOST_CHECK_NO_THROW(shapeMatrix.resize(0, 0));
  }

  BOOST_AUTO_TEST_CASE(TestResizeDecrease)
  {
    ShapeMatrix shapeMatrix(1, 3);

    BOOST_CHECK_THROW(shapeMatrix.resize(0, 0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
