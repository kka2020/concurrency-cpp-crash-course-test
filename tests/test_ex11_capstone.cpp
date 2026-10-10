// Tests for Exercise 11. Don't edit - make them pass by editing scheduler.h/.cc.
#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "scheduler.h"

using Log = std::vector<std::string>;
using Strings = std::vector<std::string>;

namespace {

// A simple item type for testing Registry<T> on its own.
struct Item {
  std::string name;
  int value;
  const std::string& Name() const { return name; }
};

std::unique_ptr<Item> MakeItem(std::string name, int value) {
  return std::make_unique<Item>(Item{name, value});
}

// A task that counts its own destruction.
class CountedTask : public Task {
 public:
  CountedTask(std::string name, int* destroyed) : Task(name), destroyed_(destroyed) { }
  ~CountedTask() { (*destroyed_)++; }
  std::string Run() override { return "counted"; }

 private:
  int* destroyed_;
};

}  // namespace

// ===================================================================== Tasks

TEST(Ex11_Tasks, EchoTask) {
  EchoTask task("greet", "hello");
  EXPECT_EQ(task.Name(), "greet");
  EXPECT_EQ(task.Run(), "hello");
  EXPECT_EQ(task.Priority(), 0) << "The default priority is 0";
}

TEST(Ex11_Tasks, LambdaTaskRunsItsFunction) {
  int calls = 0;
  LambdaTask task("count", [&calls]() { calls++; return std::to_string(calls); }, 7);
  EXPECT_EQ(task.Run(), "1");
  EXPECT_EQ(task.Run(), "2");
  EXPECT_EQ(calls, 2);
  EXPECT_EQ(task.Priority(), 7);
}

TEST(Ex11_Tasks, DispatchThroughTaskPointer) {
  std::unique_ptr<Task> task =
      std::make_unique<LambdaTask>("x", []() { return std::string("from lambda"); }, 3);
  EXPECT_EQ(task->Run(), "from lambda");
  EXPECT_EQ(task->Priority(), 3);
}

TEST(Ex11_Tasks, DestroyingThroughTaskPointerRunsSubclassDestructor) {
  int destroyed = 0;
  {
    std::unique_ptr<Task> task = std::make_unique<CountedTask>("c", &destroyed);
  }
  EXPECT_EQ(destroyed, 1);
  EXPECT_TRUE(std::has_virtual_destructor_v<Task>)
      << "Tasks are owned through std::unique_ptr<Task> - Task needs a virtual destructor";
}

// ================================================================== Registry

TEST(Ex11_Registry, AddFindAndSize) {
  Registry<Item> registry;
  EXPECT_EQ(registry.Size(), 0u);
  Item& added = registry.Add(MakeItem("a", 1));
  registry.Add(MakeItem("b", 2));
  EXPECT_EQ(added.value, 1);
  EXPECT_EQ(registry.Size(), 2u);
  Item* found = registry.Find("b");
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->value, 2);
  EXPECT_EQ(registry.Find("zzz"), nullptr);
}

TEST(Ex11_Registry, AddReturnsReferenceToStoredItem) {
  Registry<Item> registry;
  Item& added = registry.Add(MakeItem("a", 1));
  added.value = 42;
  EXPECT_EQ(registry.Find("a")->value, 42)
      << "Add should return a reference to the item the registry owns";
}

TEST(Ex11_Registry, AddRejectsNullAndDuplicates) {
  Registry<Item> registry;
  registry.Add(MakeItem("a", 1));
  EXPECT_THROW(registry.Add(nullptr), std::invalid_argument);
  EXPECT_THROW(registry.Add(MakeItem("a", 2)), std::invalid_argument);
  EXPECT_EQ(registry.Size(), 1u);
  EXPECT_EQ(registry.Find("a")->value, 1);
}

TEST(Ex11_Registry, RemoveTransfersOwnership) {
  Registry<Item> registry;
  registry.Add(MakeItem("a", 1));
  registry.Add(MakeItem("b", 2));
  registry.Add(MakeItem("c", 3));
  std::unique_ptr<Item> removed = registry.Remove("b");
  ASSERT_NE(removed, nullptr);
  EXPECT_EQ(removed->value, 2);
  EXPECT_EQ(registry.Size(), 2u);
  EXPECT_EQ(registry.Find("b"), nullptr);
  EXPECT_EQ(registry.Remove("b"), nullptr);
}

TEST(Ex11_Registry, ForEachVisitsInInsertionOrder) {
  Registry<Item> registry;
  registry.Add(MakeItem("x", 1));
  registry.Add(MakeItem("y", 2));
  registry.Add(MakeItem("z", 3));
  registry.Remove("y");
  Strings names;
  registry.ForEach([&names](Item& item) {
    names.push_back(item.Name());
    item.value *= 10;
  });
  EXPECT_EQ(names, (Strings{"x", "z"}));
  EXPECT_EQ(registry.Find("z")->value, 30) << "ForEach should give access to the real items";
}

TEST(Ex11_Registry, AuditedRegistryKeepsHistory) {
  AuditedRegistry<Item> registry;
  registry.AddAndRecord(MakeItem("a", 1));
  registry.AddAndRecord(MakeItem("b", 2));
  registry.Remove("a");
  EXPECT_THROW(registry.AddAndRecord(MakeItem("b", 3)), std::invalid_argument);
  EXPECT_EQ(registry.History(), (Strings{"a", "b"}));
  EXPECT_EQ(registry.Size(), 1u);
}

// ================================================================= Scheduler

TEST(Ex11_Scheduler, RunAllUsesPriorityThenInsertionOrder) {
  Log log;
  Scheduler scheduler(log);
  scheduler.Tasks().AddAndRecord(std::make_unique<EchoTask>("low1", "L1"));
  scheduler.Tasks().AddAndRecord(
      std::make_unique<LambdaTask>("high", []() { return std::string("H"); }, 5));
  scheduler.Tasks().AddAndRecord(std::make_unique<EchoTask>("low2", "L2"));
  scheduler.Tasks().AddAndRecord(
      std::make_unique<LambdaTask>("mid", []() { return std::string("M"); }, 2));

  EXPECT_EQ(scheduler.RunAll(), (Strings{"H", "M", "L1", "L2"}));
  EXPECT_EQ(log, (Log{"ran high", "ran mid", "ran low1", "ran low2"}));
}

TEST(Ex11_Scheduler, RunAllDoesNotRemoveTasks) {
  Log log;
  Scheduler scheduler(log);
  scheduler.Tasks().AddAndRecord(std::make_unique<EchoTask>("a", "A"));
  scheduler.RunAll();
  EXPECT_EQ(scheduler.RunAll(), (Strings{"A"}));
  EXPECT_EQ(scheduler.Tasks().Size(), 1u);
}

TEST(Ex11_Scheduler, RemoveIfDestroysMatchingTasks) {
  Log log;
  int destroyed = 0;
  Scheduler scheduler(log);
  scheduler.Tasks().AddAndRecord(std::make_unique<CountedTask>("tmp-1", &destroyed));
  scheduler.Tasks().AddAndRecord(std::make_unique<EchoTask>("keep", "K"));
  scheduler.Tasks().AddAndRecord(std::make_unique<CountedTask>("tmp-2", &destroyed));

  int removed = scheduler.RemoveIf(
      [](const Task& task) { return task.Name().rfind("tmp-", 0) == 0; });
  EXPECT_EQ(removed, 2);
  EXPECT_EQ(destroyed, 2) << "Removed tasks should be destroyed straight away";
  EXPECT_EQ(scheduler.Tasks().Size(), 1u);
  EXPECT_EQ(scheduler.Tasks().History(), (Strings{"tmp-1", "keep", "tmp-2"}));
}

TEST(Ex11_Scheduler, DestructorLogsAndDestroysRemainingTasks) {
  Log log;
  int destroyed = 0;
  {
    Scheduler scheduler(log);
    scheduler.Tasks().AddAndRecord(std::make_unique<CountedTask>("a", &destroyed));
    scheduler.Tasks().AddAndRecord(std::make_unique<CountedTask>("b", &destroyed));
  }
  EXPECT_EQ(log, (Log{"shutdown: 2 task(s) left"}));
  EXPECT_EQ(destroyed, 2);
}

TEST(Ex11_Scheduler, ConstructorIsExplicit) {
  EXPECT_FALSE((std::is_convertible_v<Log&, Scheduler>))
      << "Scheduler(std::vector<std::string>&) is a single-argument constructor";
}
