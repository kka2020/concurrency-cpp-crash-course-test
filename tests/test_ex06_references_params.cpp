// Tests for Exercise 6. Don't edit - make them pass by editing params.h/.cc.
#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <vector>

#include "params.h"

// ---------------------------------------------------------------- behaviour

TEST(Ex06_Behaviour, SwapExchangesCallersVariables) {
  int x = 1;
  int y = 2;
  Swap(x, y);
  EXPECT_EQ(x, 2);
  EXPECT_EQ(y, 1);
}

TEST(Ex06_Behaviour, IncrementAllModifiesCallersVector) {
  std::vector<int> values{1, 5, -1};
  IncrementAll(values);
  EXPECT_EQ(values, (std::vector<int>{2, 6, 0}));
}

TEST(Ex06_Behaviour, CountVowels) {
  EXPECT_EQ(CountVowels("Hello World"), 3u);
  EXPECT_EQ(CountVowels("AEIOUxyz"), 5u);
  EXPECT_EQ(CountVowels(""), 0u);
}

TEST(Ex06_Behaviour, Square) {
  EXPECT_EQ(Square(12), 144);
  EXPECT_EQ(Square(-3), 9);
}

TEST(Ex06_Behaviour, ClampTo) {
  int three = 3;
  int ten = 10;
  EXPECT_EQ(ClampTo(5, &three), 3);
  EXPECT_EQ(ClampTo(5, &ten), 5);
  EXPECT_EQ(ClampTo(5, nullptr), 5);
}

TEST(Ex06_Behaviour, ParseDigitsSuccessStoresResult) {
  int out = -1;
  EXPECT_TRUE(ParseDigits("0042", &out));
  EXPECT_EQ(out, 42);
  EXPECT_TRUE(ParseDigits("7", &out));
  EXPECT_EQ(out, 7);
}

TEST(Ex06_Behaviour, ParseDigitsFailureLeavesOutUnchanged) {
  int out = 99;
  EXPECT_FALSE(ParseDigits("", &out));
  EXPECT_FALSE(ParseDigits("-1", &out));
  EXPECT_FALSE(ParseDigits("4a", &out));
  EXPECT_FALSE(ParseDigits(" 4", &out));
  EXPECT_EQ(out, 99);
}

TEST(Ex06_Behaviour, ParseDigitsWithNullOutJustValidates) {
  EXPECT_TRUE(ParseDigits("123", nullptr));
  EXPECT_FALSE(ParseDigits("12x", nullptr));
}

TEST(Ex06_Behaviour, FindLongestPointsIntoCallersVector) {
  std::vector<std::string> words{"a", "abc", "xy", "abd"};
  const std::string* longest = FindLongest(words);
  ASSERT_NE(longest, nullptr);
  EXPECT_EQ(longest, &words[1])
      << "The pointer must point at the element in the caller's vector, not at a copy";
}

TEST(Ex06_Behaviour, FindLongestOfNothingIsNull) {
  std::vector<std::string> words;
  EXPECT_EQ(FindLongest(words), nullptr);
}

// --------------------------------------------------------------- signatures

TEST(Ex06_Signatures, Swap) {
  EXPECT_TRUE((std::is_same_v<decltype(&Swap), void (*)(int&, int&)>))
      << "Both parameters are required and modified -> int&";
}

TEST(Ex06_Signatures, IncrementAll) {
  EXPECT_TRUE((std::is_same_v<decltype(&IncrementAll), void (*)(std::vector<int>&)>))
      << "Required and modified -> std::vector<int>&";
}

TEST(Ex06_Signatures, CountVowels) {
  EXPECT_TRUE(
      (std::is_same_v<decltype(&CountVowels), std::size_t (*)(const std::string&)>))
      << "Required, not modified, expensive to copy -> const std::string&";
}

TEST(Ex06_Signatures, Square) {
  EXPECT_TRUE((std::is_same_v<decltype(&Square), int (*)(int)>))
      << "Required, not modified, cheap to copy -> plain int";
}

TEST(Ex06_Signatures, ClampTo) {
  EXPECT_TRUE((std::is_same_v<decltype(&ClampTo), int (*)(int, const int*)>))
      << "max_value is optional and only read -> const int*";
}

TEST(Ex06_Signatures, ParseDigits) {
  EXPECT_TRUE(
      (std::is_same_v<decltype(&ParseDigits), bool (*)(const std::string&, int*)>))
      << "text: required, read-only, expensive -> const std::string&; "
         "out: optional and written to -> int*";
}

TEST(Ex06_Signatures, FindLongest) {
  EXPECT_TRUE((std::is_same_v<decltype(&FindLongest),
                              const std::string* (*)(const std::vector<std::string>&)>))
      << "A by-value vector is a local copy: a pointer into it dangles once the "
         "function returns. Use const std::vector<std::string>&";
}
