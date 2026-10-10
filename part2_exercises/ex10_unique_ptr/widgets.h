// Exercise 10, part B: ownership transfer with std::unique_ptr
//
// Widget and FancyWidget are complete - implement the four functions at the
// bottom in widgets.cc. Use std::make_unique to create objects, .get() to hand
// out non-owning raw pointers, and std::move to transfer ownership.
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

class Widget {
 public:
  explicit Widget(std::string name) : name_(std::move(name)) { live++; }
  virtual ~Widget() { live--; }

  const std::string& Name() const { return name_; }
  virtual std::string Kind() const { return "plain"; }

  // How many Widgets currently exist (used by the tests to detect leaks).
  static int Live() { return live; }

 private:
  std::string name_;
  static inline int live = 0;
};

class FancyWidget : public Widget {
 public:
  explicit FancyWidget(std::string name) : Widget(std::move(name)) { }
  std::string Kind() const override { return "fancy"; }
};

// Creates a FancyWidget if `fancy` is true, otherwise a plain Widget, and gives
// ownership of it to the caller.
std::unique_ptr<Widget> MakeWidget(const std::string& name, bool fancy);

// Non-owning inspection: returns "<name> (<kind>)", e.g. "gizmo (fancy)", or
// "nothing" if w is nullptr.
std::string Inspect(const Widget* w);

// Takes ownership of `w`, and returns the name it had. The widget must be
// destroyed by the time Consume returns.
std::string Consume(std::unique_ptr<Widget> w);

// Removes the widget with the longest name (the earliest one if there's a tie)
// from `widgets` and transfers ownership of it to the caller. The vector shrinks
// by one. Returns nullptr if `widgets` is empty.
std::unique_ptr<Widget> TakeLongestNamed(std::vector<std::unique_ptr<Widget>>& widgets);
