// Tests for Exercise 3. Don't edit - make them pass by editing shapes.h/.cc.
#include <gtest/gtest.h>

#include <memory>
#include <numbers>
#include <type_traits>
#include <vector>

#include "shapes.h"

namespace {
constexpr double kPi = std::numbers::pi;
}

TEST(Ex03_Shapes, CircleAreaAndName) {
  Circle c(2.0);
  EXPECT_NEAR(c.Area(), 4 * kPi, 1e-9);
  EXPECT_EQ(c.Name(), "circle");
  EXPECT_DOUBLE_EQ(c.Radius(), 2.0);
}

TEST(Ex03_Shapes, RectangleAreaAndName) {
  Rectangle r(3.0, 4.5);
  EXPECT_DOUBLE_EQ(r.Area(), 13.5);
  EXPECT_EQ(r.Name(), "rectangle");
}

TEST(Ex03_Shapes, SquareAreaAndName) {
  Square s(3.0);
  EXPECT_DOUBLE_EQ(s.Area(), 9.0) << "Square should pass its side to Rectangle's constructor";
  EXPECT_EQ(s.Name(), "square (a kind of rectangle)");
}

TEST(Ex03_Dispatch, MethodsDispatchOnActualTypeThroughBasePointer) {
  std::unique_ptr<Shape> shape = std::make_unique<Circle>(1.0);
  EXPECT_NEAR(shape->Area(), kPi, 1e-9)
      << "Calling Area() through a Shape* ran Shape's version: is it virtual?";
  EXPECT_EQ(shape->Name(), "circle");
}

TEST(Ex03_Dispatch, MethodsDispatchOnActualTypeThroughBaseReference) {
  Square square(2.0);
  Rectangle& as_rectangle = square;
  Shape& as_shape = square;
  EXPECT_EQ(as_rectangle.Name(), "square (a kind of rectangle)");
  EXPECT_EQ(as_shape.Name(), "square (a kind of rectangle)");
  EXPECT_DOUBLE_EQ(as_shape.Area(), 4.0);
}

TEST(Ex03_Dispatch, NonVirtualDescribeStillUsesTheRightName) {
  Circle c(1.0);
  Rectangle r(1.0, 2.0);
  EXPECT_EQ(c.Describe(), "I am a circle")
      << "Describe() is a Shape method: its call to Name() only reaches Circle::Name "
         "if Name is virtual";
  EXPECT_EQ(r.Describe(), "I am a rectangle");
}

TEST(Ex03_Dispatch, TotalAreaOfMixedShapes) {
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Circle>(1.0));
  shapes.push_back(std::make_unique<Rectangle>(2.0, 3.0));
  shapes.push_back(std::make_unique<Square>(2.0));
  EXPECT_NEAR(TotalArea(shapes), kPi + 6.0 + 4.0, 1e-9);
}

TEST(Ex03_Dispatch, TotalAreaOfNothingIsZero) {
  std::vector<std::unique_ptr<Shape>> shapes;
  EXPECT_DOUBLE_EQ(TotalArea(shapes), 0.0);
}

TEST(Ex03_Dispatch, LargestName) {
  std::vector<std::unique_ptr<Shape>> shapes;
  EXPECT_EQ(LargestName(shapes), "");
  shapes.push_back(std::make_unique<Rectangle>(1.0, 2.0));
  shapes.push_back(std::make_unique<Square>(2.0));
  shapes.push_back(std::make_unique<Circle>(1.0));
  shapes.push_back(std::make_unique<Rectangle>(2.0, 2.0));
  EXPECT_EQ(LargestName(shapes), "square (a kind of rectangle)");
}

TEST(Ex03_Design, ShapeIsAbstract) {
  EXPECT_TRUE(std::is_abstract_v<Shape>)
      << "Shape should have pure virtual (= 0) methods so it can't be instantiated";
}

TEST(Ex03_Design, ShapeHasVirtualDestructor) {
  EXPECT_TRUE(std::has_virtual_destructor_v<Shape>)
      << "Shapes are deleted through std::unique_ptr<Shape>. Without a virtual "
         "destructor, ~Circle would not run - undefined behaviour.";
}

TEST(Ex03_Design, SingleArgumentConstructorsAreExplicit) {
  EXPECT_FALSE((std::is_convertible_v<double, Circle>));
  EXPECT_FALSE((std::is_convertible_v<double, Square>));
}
