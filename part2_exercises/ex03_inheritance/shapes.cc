#include "shapes.h"

#include <numbers>
#include <stdexcept>

// TODO: implement everything below.

Circle::Circle(double radius) {
  throw std::logic_error("TODO: implement Circle(radius)");
}

double Circle::Area() const {
  throw std::logic_error("TODO: implement Circle::Area");
}

std::string Circle::Name() const {
  throw std::logic_error("TODO: implement Circle::Name");
}

double Circle::Radius() const {
  throw std::logic_error("TODO: implement Circle::Radius");
}

Rectangle::Rectangle(double width, double height) {
  throw std::logic_error("TODO: implement Rectangle(width, height)");
}

double Rectangle::Area() const {
  throw std::logic_error("TODO: implement Rectangle::Area");
}

std::string Rectangle::Name() const {
  throw std::logic_error("TODO: implement Rectangle::Name");
}

// TODO: Rectangle has no default constructor, so Square's constructor has to
// say which Rectangle constructor to use. Fix the arguments below.
Square::Square(double side) : Rectangle(0, 0) {
  throw std::logic_error("TODO: implement Square(side)");
}

std::string Square::Name() const {
  throw std::logic_error("TODO: implement Square::Name");
}

double TotalArea(const std::vector<std::unique_ptr<Shape>>& shapes) {
  throw std::logic_error("TODO: implement TotalArea");
}

std::string LargestName(const std::vector<std::unique_ptr<Shape>>& shapes) {
  throw std::logic_error("TODO: implement LargestName");
}
