// Exercise 5 - model solution.
#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

template <typename T>
class Stack {
 public:
  void Push(const T& value) { items_.push_back(value); }

  void Pop() {
    if (items_.empty()) {
      throw std::out_of_range("Pop on empty stack");
    }
    items_.pop_back();
  }

  const T& Top() const {
    if (items_.empty()) {
      throw std::out_of_range("Top on empty stack");
    }
    return items_.back();
  }

  bool Empty() const { return items_.empty(); }

  std::size_t Size() const { return items_.size(); }

 private:
  std::vector<T> items_;
};

template <typename T>
T MaxOf(const T& a, const T& b) {
  // Only uses <. "a < b" is false when they're equal, so a is returned.
  return a < b ? b : a;
}

template <typename T>
T Sum(const std::vector<T>& values) {
  T total{};
  for (const auto& value : values) {
    total = total + value;
  }
  return total;
}

template <typename T>
class CountingStack : public Stack<T> {
 public:
  void PushAll(const std::vector<T>& values) {
    for (const auto& value : values) {
      // The base class depends on T, so the compiler won't find Push without this->.
      this->Push(value);
      total_pushed_++;
    }
  }

  T PopValue() {
    T top = this->Top();  // Throws std::out_of_range if empty.
    this->Pop();
    return top;
  }

  int TotalPushed() const { return total_pushed_; }

 private:
  int total_pushed_ = 0;
};
