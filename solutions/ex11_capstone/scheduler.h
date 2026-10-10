// Exercise 11 - model solution.
#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// ===================================================================== Tasks

class Task {
 public:
  explicit Task(std::string name);
  // Virtual: tasks are destroyed through std::unique_ptr<Task>.
  virtual ~Task();

  const std::string& Name() const;
  virtual std::string Run() = 0;
  virtual int Priority() const;

 private:
  std::string name_;
};

class EchoTask : public Task {
 public:
  EchoTask(std::string name, std::string message);
  std::string Run() override;

 private:
  std::string message_;
};

class LambdaTask : public Task {
 public:
  LambdaTask(std::string name, std::function<std::string()> fn, int priority);
  std::string Run() override;
  int Priority() const override;

 private:
  std::function<std::string()> fn_;
  int priority_;
};

// ================================================================== Registry

template <typename T>
class Registry {
 public:
  T& Add(std::unique_ptr<T> item) {
    if (item == nullptr) {
      throw std::invalid_argument("cannot add nullptr");
    }
    if (Find(item->Name()) != nullptr) {
      throw std::invalid_argument("duplicate name: " + item->Name());
    }
    T& added = *item;
    items_.push_back(std::move(item));
    return added;
  }

  std::size_t Size() const { return items_.size(); }

  T* Find(const std::string& name) const {
    for (const auto& item : items_) {
      if (item->Name() == name) {
        return item.get();
      }
    }
    return nullptr;
  }

  std::unique_ptr<T> Remove(const std::string& name) {
    for (auto it = items_.begin(); it != items_.end(); ++it) {
      if ((*it)->Name() == name) {
        std::unique_ptr<T> removed = std::move(*it);
        items_.erase(it);
        return removed;
      }
    }
    return nullptr;
  }

  void ForEach(const std::function<void(T&)>& fn) const {
    for (const auto& item : items_) {
      fn(*item);
    }
  }

 private:
  std::vector<std::unique_ptr<T>> items_;
};

template <typename T>
class AuditedRegistry : public Registry<T> {
 public:
  T& AddAndRecord(std::unique_ptr<T> item) {
    // this-> is required: Add lives in Registry<T>, which depends on T.
    T& added = this->Add(std::move(item));
    history_.push_back(added.Name());
    return added;
  }

  const std::vector<std::string>& History() const { return history_; }

 private:
  std::vector<std::string> history_;
};

// ================================================================= Scheduler

class Scheduler {
 public:
  explicit Scheduler(std::vector<std::string>& log);
  ~Scheduler();

  AuditedRegistry<Task>& Tasks();
  std::vector<std::string> RunAll();
  int RemoveIf(const std::function<bool(const Task&)>& pred);

 private:
  std::vector<std::string>& log_;
  AuditedRegistry<Task> tasks_;
};
