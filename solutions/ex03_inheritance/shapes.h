// Exercise 3 - model solution.
#pragma once

#include <memory>
#include <string>
#include <vector>

class Shape {
 public:
  // Virtual: shapes are deleted through Shape pointers (std::unique_ptr<Shape>).
  virtual ~Shape() { }

  // Pure virtual: makes Shape abstract and forces subclasses to provide them.
  virtual double Area() const = 0;
  virtual std::string Name() const = 0;

  // Name() is virtual, so this calls the subclass's Name().
  std::string Describe() const { return "I am a " + Name(); }
};

class Circle : public Shape {
 public:
  explicit Circle(double radius);
  double Area() const override;
  std::string Name() const override;
  double Radius() const;

 private:
  double radius_;
};

class Rectangle : public Shape {
 public:
  Rectangle(double width, double height);
  double Area() const override;
  std::string Name() const override;

 private:
  double width_;
  double height_;
};

class Square : public Rectangle {
 public:
  explicit Square(double side);
  std::string Name() const override;
};

double TotalArea(const std::vector<std::unique_ptr<Shape>>& shapes);
std::string LargestName(const std::vector<std::unique_ptr<Shape>>& shapes);
