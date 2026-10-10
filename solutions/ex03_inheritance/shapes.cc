#include "shapes.h"

#include <numbers>

Circle::Circle(double radius) : radius_(radius) { }

double Circle::Area() const {
  return std::numbers::pi * radius_ * radius_;
}

std::string Circle::Name() const {
  return "circle";
}

double Circle::Radius() const {
  return radius_;
}

Rectangle::Rectangle(double width, double height) : width_(width), height_(height) { }

double Rectangle::Area() const {
  return width_ * height_;
}

std::string Rectangle::Name() const {
  return "rectangle";
}

Square::Square(double side) : Rectangle(side, side) { }

std::string Square::Name() const {
  return "square (a kind of " + Rectangle::Name() + ")";
}

double TotalArea(const std::vector<std::unique_ptr<Shape>>& shapes) {
  double total = 0.0;
  for (const auto& shape : shapes) {
    total += shape->Area();
  }
  return total;
}

std::string LargestName(const std::vector<std::unique_ptr<Shape>>& shapes) {
  const Shape* largest = nullptr;
  for (const auto& shape : shapes) {
    if (largest == nullptr || shape->Area() > largest->Area()) {
      largest = shape.get();
    }
  }
  return largest == nullptr ? "" : largest->Name();
}
