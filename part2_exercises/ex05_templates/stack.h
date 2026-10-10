// Exercise 5: templates (C++ generics)
//
// Concepts: class templates, function templates, the implicit requirements a
// template puts on its type parameters, and deriving one class template from
// another (remember the crash course's "detail on templates and inheritance").
//
// Templates are normally written entirely in the header (the compiler needs the
// full definition to compile each instantiation), so everything goes in this file.
// Replace each `throw` with a real implementation.
//
// Tests: tests/test_ex05_templates.cpp    Run configuration: ex05_templates_test
#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

// A last-in, first-out stack of T values, stored in a std::vector<T>.
template <typename T>
class Stack {
 public:
  // Puts `value` on top of the stack.
  void Push(const T& value) { throw std::logic_error("TODO: Stack::Push"); }

  // Removes the top value. Throws std::out_of_range if the stack is empty.
  void Pop() { throw std::logic_error("TODO: Stack::Pop"); }

  // Returns the top value. Throws std::out_of_range if the stack is empty.
  const T& Top() const { throw std::logic_error("TODO: Stack::Top"); }

  bool Empty() const { throw std::logic_error("TODO: Stack::Empty"); }

  std::size_t Size() const { throw std::logic_error("TODO: Stack::Size"); }

 private:
  std::vector<T> items_;
};

// Returns the larger of a and b; if neither is larger, returns a.
// Must only require operator< on T (the tests use a type that has no operator>).
template <typename T>
T MaxOf(const T& a, const T& b) {
  throw std::logic_error("TODO: MaxOf");
}

// Returns the sum of all values, starting from T{} - so the sum of an empty
// vector is T{} (0 for numbers, "" for strings).
template <typename T>
T Sum(const std::vector<T>& values) {
  throw std::logic_error("TODO: Sum");
}

// A Stack that also counts how many values were pushed through PushAll.
// Implement these methods by calling the INHERITED Stack<T> methods.
template <typename T>
class CountingStack : public Stack<T> {
 public:
  // Pushes each value in order (so the last one ends up on top).
  void PushAll(const std::vector<T>& values) {
    throw std::logic_error("TODO: CountingStack::PushAll");
  }

  // Removes and returns the top value. Throws std::out_of_range if empty.
  T PopValue() { throw std::logic_error("TODO: CountingStack::PopValue"); }

  // Total number of values ever pushed via PushAll.
  int TotalPushed() const { throw std::logic_error("TODO: CountingStack::TotalPushed"); }

 private:
  int total_pushed_ = 0;
};
