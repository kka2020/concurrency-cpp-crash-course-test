// Exercise 3: inheritance, virtual methods and abstract classes
//
// Concepts: public inheritance, calling a base-class constructor, calling a
// base-class method (Base::Method()), virtual vs non-virtual dispatch,
// override, pure virtual methods (= 0), virtual destructors.
//
// The skeleton below compiles, but Shape is not a proper polymorphic base class
// yet: calling Area() or Name() through a Shape* or Shape& always runs the Shape
// versions. Your job:
//   * Make Shape ABSTRACT: there is no sensible Area() or Name() for a general shape.
//   * Make sure deleting a Circle through a std::unique_ptr<Shape> runs ~Circle.
//   * Mark the subclass methods that override something with `override`.
//   * Follow the crash course's advice for single-argument constructors.
//   * Describe() must stay non-virtual - but it must still report the right name.
//   * Implement everything in shapes.cc.
//
// Tests: tests/test_ex03_inheritance.cpp    Run configuration: ex03_inheritance_test
#pragma once

#include <memory>
#include <string>
#include <vector>

class Shape {
 public:
  ~Shape() { }

  double Area() const { return 0.0; }           // TODO
  std::string Name() const { return "shape"; }  // TODO

  // Not virtual on purpose. Already implemented.
  std::string Describe() const { return "I am a " + Name(); }
};

class Circle : public Shape {
 public:
  explicit Circle(double radius);
  double Area() const;      // pi * r * r  (std::numbers::pi is in <numbers>)
  std::string Name() const; // "circle"
  double Radius() const;

 private:
  double radius_;
};

class Rectangle : public Shape {
 public:
  Rectangle(double width, double height);
  double Area() const;      // width * height
  std::string Name() const; // "rectangle"

 private:
  double width_;
  double height_;
};

// A square is a rectangle whose width equals its height.
class Square : public Rectangle {
 public:
  explicit Square(double side);  // must reuse the Rectangle constructor
  // "square (a kind of rectangle)" - build it by calling Rectangle's Name().
  std::string Name() const;
};

// Sum of the areas of all the shapes.
double TotalArea(const std::vector<std::unique_ptr<Shape>>& shapes);

// Name of the shape with the largest area ("" if there are no shapes).
// If several share the largest area, return the first one's name.
std::string LargestName(const std::vector<std::unique_ptr<Shape>>& shapes);
