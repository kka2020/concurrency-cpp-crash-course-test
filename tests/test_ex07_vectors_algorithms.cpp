// Tests for Exercise 7. Don't edit - make them pass by editing algos.cc.
#include <gtest/gtest.h>

#include <map>
#include <string>
#include <vector>

#include "algos.h"

using Words = std::vector<std::string>;
using Ints = std::vector<int>;

TEST(Ex07_Vectors, Contains) {
  Words words{"Hello", "World"};
  EXPECT_TRUE(Contains(words, "Hello"));
  EXPECT_TRUE(Contains(words, "World"));
  EXPECT_FALSE(Contains(words, "hello"));
  EXPECT_FALSE(Contains(Words{}, "Hello"));
}

TEST(Ex07_Vectors, IndexOf) {
  Ints values{4, 8, 15, 16, 23, 42, 8};
  EXPECT_EQ(IndexOf(values, 4), 0);
  EXPECT_EQ(IndexOf(values, 8), 1) << "Should find the FIRST occurrence";
  EXPECT_EQ(IndexOf(values, 42), 5);
  EXPECT_EQ(IndexOf(values, 7), -1);
}

TEST(Ex07_Vectors, RemoveFirstRemovesOnlyFirstOccurrence) {
  Words words{"a", "b", "a", "c"};
  EXPECT_TRUE(RemoveFirst(words, "a"));
  EXPECT_EQ(words, (Words{"b", "a", "c"}));
}

TEST(Ex07_Vectors, RemoveFirstOfMissingWordChangesNothing) {
  Words words{"a", "b"};
  EXPECT_FALSE(RemoveFirst(words, "z"))
      << "If std::find returns end(), there is nothing to erase";
  EXPECT_EQ(words, (Words{"a", "b"}));
}

TEST(Ex07_Vectors, RemoveAll) {
  Ints values{1, 2, 1, 1, 3, 1};
  RemoveAll(values, 1);
  EXPECT_EQ(values, (Ints{2, 3}));
  RemoveAll(values, 9);
  EXPECT_EQ(values, (Ints{2, 3}));
}

TEST(Ex07_Vectors, AppendToAllModifiesElements) {
  Words words{"Hello", "World"};
  AppendToAll(words, "!");
  EXPECT_EQ(words, (Words{"Hello!", "World!"}))
      << "A range-for loop by value modifies copies - iterate by reference";
}

TEST(Ex07_Vectors, UniqueInOrder) {
  EXPECT_EQ(UniqueInOrder({3, 1, 3, 2, 1}), (Ints{3, 1, 2}));
  EXPECT_EQ(UniqueInOrder({}), Ints{});
  EXPECT_EQ(UniqueInOrder({5, 5, 5}), (Ints{5}));
}

TEST(Ex07_Bonus, CountOccurrencesWithMap) {
  auto counts = CountOccurrences({"to", "be", "or", "not", "to", "be"});
  std::map<std::string, int> expected{{"to", 2}, {"be", 2}, {"or", 1}, {"not", 1}};
  EXPECT_EQ(counts, expected);
}
