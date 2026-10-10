// Exercise 11: capstone - a tiny task scheduler
//
// Uses everything from the crash course together: classes, the .h/.cc split,
// inheritance and virtual methods, abstract classes, class templates (including
// deriving from one), std::unique_ptr ownership, vectors + <algorithm>,
// std::function + lambdas, destructors, and explicit constructors.
//
// Task, EchoTask, LambdaTask and Scheduler are implemented in scheduler.cc.
// Registry and AuditedRegistry are templates, so they're implemented right here.
// Some declarations below are incomplete on purpose - the tests will tell you.
//
// Tests: tests/test_ex11_capstone.cpp    Run configuration: ex11_capstone_test
#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// ===================================================================== Tasks

// Abstract base class of every task. Tasks are always owned through
// std::unique_ptr<Task>.
class Task {
 public:
  explicit Task(std::string name);
  ~Task();

  const std::string& Name() const;

  // Runs the task and returns its result.
  virtual std::string Run() = 0;

  // Tasks with a higher priority run first. The default priority is 0.
  virtual int Priority() const;

 private:
  std::string name_;
};

// A task that returns the same message every time it runs.
class EchoTask : public Task {
 public:
  EchoTask(std::string name, std::string message);
  std::string Run() override;

 private:
  std::string message_;
};

// A task that runs an arbitrary function, with a custom priority.
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

// Owns a collection of T objects, in insertion order. T must have a Name()
// method, and names are unique within a registry.
template <typename T>
class Registry {
 public:
  // Takes ownership of `item` and returns a reference to it.
  // Throws std::invalid_argument if item is nullptr or if an item with the same
  // name is already registered.
  T& Add(std::unique_ptr<T> item) { throw std::logic_error("TODO: Registry::Add"); }

  std::size_t Size() const { throw std::logic_error("TODO: Registry::Size"); }

  // Non-owning lookup: a pointer to the item called `name`, or nullptr.
  T* Find(const std::string& name) const { throw std::logic_error("TODO: Registry::Find"); }

  // Removes the item called `name` and transfers ownership of it to the caller.
  // Returns nullptr if there is no such item.
  std::unique_ptr<T> Remove(const std::string& name) {
    throw std::logic_error("TODO: Registry::Remove");
  }

  // Calls fn on every item, in insertion order.
  void ForEach(const std::function<void(T&)>& fn) const {
    throw std::logic_error("TODO: Registry::ForEach");
  }

 private:
  std::vector<std::unique_ptr<T>> items_;
};

// A Registry that also remembers the name of every item that was ever added
// through AddAndRecord (even after it is removed). Implement it using the
// inherited Registry<T> methods.
template <typename T>
class AuditedRegistry : public Registry<T> {
 public:
  // Like Add, but also records the item's name. If Add throws, nothing is recorded.
  T& AddAndRecord(std::unique_ptr<T> item) {
    throw std::logic_error("TODO: AuditedRegistry::AddAndRecord");
  }

  const std::vector<std::string>& History() const {
    throw std::logic_error("TODO: AuditedRegistry::History");
  }

 private:
  std::vector<std::string> history_;
};

// ================================================================= Scheduler

class Scheduler {
 public:
  // `log` receives the scheduler's messages (see RunAll and ~Scheduler).
  Scheduler(std::vector<std::string>& log);

  // Appends "shutdown: <N> task(s) left" to the log, where N is the number of
  // tasks still registered, e.g. "shutdown: 2 task(s) left".
  ~Scheduler();

  AuditedRegistry<Task>& Tasks();

  // Runs every task, highest Priority() first; tasks with equal priority run in
  // the order they were added. Appends "ran <name>" to the log for each task,
  // and returns the results of Run() in the order the tasks ran.
  std::vector<std::string> RunAll();

  // Removes (and so destroys) every task for which pred(task) is true.
  // Returns how many tasks were removed.
  int RemoveIf(const std::function<bool(const Task&)>& pred);

 private:
  std::vector<std::string>& log_;
  AuditedRegistry<Task> tasks_;
};
