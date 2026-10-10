// Exercise 10, part A: a singly linked list built from std::unique_ptr
// (the crash course's "live coding demo").
//
// Rules:
//   * No `new` and no `delete`.
//   * Every node is owned by exactly one std::unique_ptr: head_ owns the first
//     node, and each node's `next` owns the node after it.
//   * Use raw pointers (from .get()) only to WALK the list without owning it.
//   * Use std::move (from <utility>) to transfer ownership between unique_ptrs.
//
// Implement the methods in linked_list.cc.
//
// Tests: tests/test_ex10_unique_ptr.cpp    Run configuration: ex10_unique_ptr_test
#pragma once

#include <cstddef>
#include <memory>
#include <vector>

class IntList {
 public:
  IntList() = default;

  void PushFront(int value);
  void PushBack(int value);  // Walking to the end each time is fine.

  // Removes the first node and returns its value. Throws std::out_of_range if empty.
  int PopFront();

  // Returns the first value. Throws std::out_of_range if empty.
  int Front() const;

  std::size_t Size() const;
  bool Empty() const;
  bool Contains(int value) const;

  // Reverses the list IN PLACE by relinking the existing nodes - don't create
  // any new nodes.
  void Reverse();

  // The values from front to back.
  std::vector<int> ToVector() const;

  // How many Node objects are currently alive, across ALL lists. The tests use
  // it to detect leaks and accidental extra nodes. Already implemented.
  static int LiveNodes() { return Node::live; }

 private:
  struct Node {
    explicit Node(int v) : value(v) { live++; }
    ~Node() { live--; }

    int value;
    std::unique_ptr<Node> next;

    static inline int live = 0;
  };

  std::unique_ptr<Node> head_;
  std::size_t size_ = 0;
};
