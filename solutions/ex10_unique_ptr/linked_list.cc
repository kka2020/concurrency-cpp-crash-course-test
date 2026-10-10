#include "linked_list.h"

#include <stdexcept>
#include <utility>

void IntList::PushFront(int value) {
  auto node = std::make_unique<Node>(value);
  node->next = std::move(head_);  // The new node takes over the old first node...
  head_ = std::move(node);        // ...and head_ takes over the new node.
  size_++;
}

void IntList::PushBack(int value) {
  if (!head_) {
    PushFront(value);
    return;
  }
  Node* current = head_.get();  // Non-owning: just walking.
  while (current->next) {
    current = current->next.get();
  }
  current->next = std::make_unique<Node>(value);
  size_++;
}

int IntList::PopFront() {
  if (!head_) {
    throw std::out_of_range("PopFront on empty list");
  }
  int value = head_->value;
  // Assigning head_ releases the old first node, which is destroyed here.
  head_ = std::move(head_->next);
  size_--;
  return value;
}

int IntList::Front() const {
  if (!head_) {
    throw std::out_of_range("Front on empty list");
  }
  return head_->value;
}

std::size_t IntList::Size() const {
  return size_;
}

bool IntList::Empty() const {
  return size_ == 0;
}

bool IntList::Contains(int value) const {
  for (const Node* current = head_.get(); current != nullptr; current = current->next.get()) {
    if (current->value == value) {
      return true;
    }
  }
  return false;
}

void IntList::Reverse() {
  std::unique_ptr<Node> reversed;
  while (head_) {
    std::unique_ptr<Node> rest = std::move(head_->next);
    head_->next = std::move(reversed);
    reversed = std::move(head_);
    head_ = std::move(rest);
  }
  head_ = std::move(reversed);
}

std::vector<int> IntList::ToVector() const {
  std::vector<int> result;
  for (const Node* current = head_.get(); current != nullptr; current = current->next.get()) {
    result.push_back(current->value);
  }
  return result;
}
