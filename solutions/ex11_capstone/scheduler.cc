#include "scheduler.h"

#include <algorithm>

// ===================================================================== Tasks

Task::Task(std::string name) : name_(name) { }

Task::~Task() { }

const std::string& Task::Name() const {
  return name_;
}

int Task::Priority() const {
  return 0;
}

EchoTask::EchoTask(std::string name, std::string message)
    : Task(name), message_(message) { }

std::string EchoTask::Run() {
  return message_;
}

LambdaTask::LambdaTask(std::string name, std::function<std::string()> fn, int priority)
    : Task(name), fn_(fn), priority_(priority) { }

std::string LambdaTask::Run() {
  return fn_();
}

int LambdaTask::Priority() const {
  return priority_;
}

// ================================================================= Scheduler

Scheduler::Scheduler(std::vector<std::string>& log) : log_(log) { }

Scheduler::~Scheduler() {
  log_.push_back("shutdown: " + std::to_string(tasks_.Size()) + " task(s) left");
}  // tasks_ is destroyed after this body, destroying the remaining tasks.

AuditedRegistry<Task>& Scheduler::Tasks() {
  return tasks_;
}

std::vector<std::string> Scheduler::RunAll() {
  // Collect non-owning pointers - the registry keeps ownership.
  std::vector<Task*> order;
  tasks_.ForEach([&order](Task& task) { order.push_back(&task); });

  // stable_sort keeps insertion order among tasks with equal priority.
  std::stable_sort(order.begin(), order.end(), [](const Task* a, const Task* b) {
    return a->Priority() > b->Priority();
  });

  std::vector<std::string> results;
  for (Task* task : order) {
    results.push_back(task->Run());
    log_.push_back("ran " + task->Name());
  }
  return results;
}

int Scheduler::RemoveIf(const std::function<bool(const Task&)>& pred) {
  // Don't remove while ForEach is iterating - collect the names first.
  std::vector<std::string> doomed;
  tasks_.ForEach([&doomed, &pred](Task& task) {
    if (pred(task)) {
      doomed.push_back(task.Name());
    }
  });
  for (const auto& name : doomed) {
    tasks_.Remove(name);  // The returned unique_ptr is discarded, destroying the task.
  }
  return static_cast<int>(doomed.size());
}
