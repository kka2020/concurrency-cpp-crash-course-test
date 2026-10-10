// Tests for Exercise 9. Don't edit - make them pass by editing raii.cc.
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "raii.h"

using Log = std::vector<std::string>;

TEST(Ex09_Lifetime, LoggerLogsEnterAndExit) {
  Log log;
  {
    ScopedLogger logger("a", log);
    EXPECT_EQ(log, (Log{"enter a"})) << "The constructor should log \"enter a\"";
  }
  EXPECT_EQ(log, (Log{"enter a", "exit a"})) << "The destructor should log \"exit a\"";
}

TEST(Ex09_Lifetime, SameScopeDestroyedInReverseOrder) {
  Log log;
  {
    ScopedLogger first("first", log);
    ScopedLogger second("second", log);
  }
  EXPECT_EQ(log, (Log{"enter first", "enter second", "exit second", "exit first"}));
}

TEST(Ex09_Lifetime, NestedScopes) {
  Log log;
  {
    ScopedLogger outer("outer", log);
    {
      ScopedLogger inner("inner", log);
    }
    ScopedLogger after("after", log);
  }
  EXPECT_EQ(log, (Log{"enter outer", "enter inner", "exit inner", "enter after",
                      "exit after", "exit outer"}));
}

TEST(Ex09_Composite, PipelineConstructionAndDestructionOrder) {
  Log log;
  {
    Pipeline pipeline(log);
    EXPECT_EQ(log, (Log{"enter source", "enter sink", "pipeline ready"}))
        << "Fields are constructed in declaration order, BEFORE the constructor body";
  }
  EXPECT_EQ(log, (Log{"enter source", "enter sink", "pipeline ready", "pipeline done",
                      "exit sink", "exit source"}))
      << "The destructor body runs first, then fields are destroyed in reverse order";
}

TEST(Ex09_Composite, HeapObjectDestroyedWhenUniquePtrDies) {
  Log log;
  {
    auto owner = std::make_unique<Pipeline>(log);
    log.push_back("owner alive");
  }
  EXPECT_EQ(log.back(), "exit source");
  EXPECT_EQ(log.size(), 7u);
}

TEST(Ex09_Puzzle, RunScopesProducesExactSequence) {
  Log log;
  RunScopes(log);
  EXPECT_EQ(log, (Log{"enter main", "enter setup", "exit setup", "enter work",
                      "enter step1", "enter step2", "exit step2", "exit step1",
                      "exit work", "enter cleanup", "exit cleanup", "exit main"}));
}
