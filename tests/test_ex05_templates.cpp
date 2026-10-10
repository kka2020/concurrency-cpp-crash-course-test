// Tests for Exercise 5. Don't edit - make them pass by editing stack.h.
#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "stack.h"

namespace {

// Has operator< but deliberately NOT operator>.
struct Version {
  int major;
  int minor;
  char tag;  // Not part of the ordering - lets the tests see WHICH argument was returned.
  bool operator<(const Version& other) const {
    return major < other.major || (major == other.major && minor < other.minor);
  }
};

}  // namespace

TEST(Ex05_Stack, StartsEmpty) {
  Stack<int> s;
  EXPECT_TRUE(s.Empty());
  EXPECT_EQ(s.Size(), 0u);
}

TEST(Ex05_Stack, PushAndTop) {
  Stack<int> s;
  s.Push(1);
  s.Push(2);
  EXPECT_FALSE(s.Empty());
  EXPECT_EQ(s.Size(), 2u);
  EXPECT_EQ(s.Top(), 2);
}

TEST(Ex05_Stack, PopIsLastInFirstOut) {
  Stack<int> s;
  s.Push(1);
  s.Push(2);
  s.Push(3);
  s.Pop();
  EXPECT_EQ(s.Top(), 2);
  s.Pop();
  EXPECT_EQ(s.Top(), 1);
  s.Pop();
  EXPECT_TRUE(s.Empty());
}

TEST(Ex05_Stack, PopAndTopOnEmptyThrowOutOfRange) {
  Stack<int> s;
  EXPECT_THROW(s.Pop(), std::out_of_range);
  EXPECT_THROW(s.Top(), std::out_of_range);
}

TEST(Ex05_Stack, WorksWithStrings) {
  Stack<std::string> s;
  s.Push("hello");
  s.Push("world");
  EXPECT_EQ(s.Top(), "world");
  s.Pop();
  EXPECT_EQ(s.Top(), "hello");
}

TEST(Ex05_FunctionTemplates, MaxOfNumbersAndStrings) {
  EXPECT_EQ(MaxOf(3, 7), 7);
  EXPECT_EQ(MaxOf(7, 3), 7);
  EXPECT_DOUBLE_EQ(MaxOf(-1.5, -2.5), -1.5);
  EXPECT_EQ(MaxOf(std::string("apple"), std::string("banana")), "banana");
}

TEST(Ex05_FunctionTemplates, MaxOfOnlyNeedsLessThan) {
  Version a{1, 2, 'a'};
  Version b{1, 10, 'b'};
  EXPECT_EQ(MaxOf(a, b).tag, 'b');
  EXPECT_EQ(MaxOf(b, a).tag, 'b');
}

TEST(Ex05_FunctionTemplates, MaxOfEqualValuesReturnsFirst) {
  Version a{2, 0, 'a'};
  Version b{2, 0, 'b'};
  EXPECT_EQ(MaxOf(a, b).tag, 'a');
}

TEST(Ex05_FunctionTemplates, SumOfNumbers) {
  EXPECT_EQ(Sum(std::vector<int>{1, 2, 3, 4}), 10);
  EXPECT_DOUBLE_EQ(Sum(std::vector<double>{0.5, 0.25}), 0.75);
  EXPECT_EQ(Sum(std::vector<int>{}), 0);
}

TEST(Ex05_FunctionTemplates, SumOfStringsConcatenates) {
  EXPECT_EQ(Sum(std::vector<std::string>{"a", "b", "c"}), "abc")
      << "Sum only needs T{} and +, so it works for std::string too";
  EXPECT_EQ(Sum(std::vector<std::string>{}), "");
}

TEST(Ex05_TemplateInheritance, PushAllAndPopValue) {
  CountingStack<int> s;
  s.PushAll({1, 2, 3});
  EXPECT_EQ(s.Size(), 3u);
  EXPECT_EQ(s.PopValue(), 3);
  EXPECT_EQ(s.PopValue(), 2);
  EXPECT_EQ(s.Size(), 1u);
}

TEST(Ex05_TemplateInheritance, TotalPushedCountsEveryPushAll) {
  CountingStack<std::string> s;
  s.PushAll({"a", "b"});
  s.PopValue();
  s.PushAll({"c"});
  EXPECT_EQ(s.TotalPushed(), 3);
  EXPECT_EQ(s.Top(), "c");
}

TEST(Ex05_TemplateInheritance, PopValueOnEmptyThrows) {
  CountingStack<int> s;
  EXPECT_THROW(s.PopValue(), std::out_of_range);
}
