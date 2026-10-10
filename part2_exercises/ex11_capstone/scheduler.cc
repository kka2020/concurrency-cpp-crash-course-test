#include "scheduler.h"

#include <algorithm>
#include <stdexcept>

// TODO: implement everything below.
// (Destructors must not throw, so the destructor stubs are simply empty.)

// ===================================================================== Tasks

Task::Task(std::string name) {
  throw std::logic_error("TODO: implement Task(name)");
}

Task::~Task() {
  // TODO
}

const std::string& Task::Name() const {
  throw std::logic_error("TODO: implement Task::Name");
}

int Task::Priority() const {
  throw std::logic_error("TODO: implement Task::Priority");
}

EchoTask::EchoTask(std::string name, std::string message) : Task(name) {
  throw std::logic_error("TODO: implement EchoTask(name, message)");
}

std::string EchoTask::Run() {
  throw std::logic_error("TODO: implement EchoTask::Run");
}

LambdaTask::LambdaTask(std::string name, std::function<std::string()> fn, int priority)
    : Task(name) {
  throw std::logic_error("TODO: implement LambdaTask(name, fn, priority)");
}

std::string LambdaTask::Run() {
  throw std::logic_error("TODO: implement LambdaTask::Run");
}

int LambdaTask::Priority() const {
  throw std::logic_error("TODO: implement LambdaTask::Priority");
}

// ================================================================= Scheduler

Scheduler::Scheduler(std::vector<std::string>& log) : log_(log) { }

Scheduler::~Scheduler() {
  // TODO
}

AuditedRegistry<Task>& Scheduler::Tasks() {
  return tasks_;
}

std::vector<std::string> Scheduler::RunAll() {
  throw std::logic_error("TODO: implement Scheduler::RunAll");
}

int Scheduler::RemoveIf(const std::function<bool(const Task&)>& pred) {
  throw std::logic_error("TODO: implement Scheduler::RemoveIf");
}
