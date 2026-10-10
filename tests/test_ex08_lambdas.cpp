// Tests for Exercise 8. Don't edit - make them pass by editing lambdas.cc.
#include <gtest/gtest.h>

#include <functional>
#include <vector>

#include "lambdas.h"

namespace {
int TimesTwo(int x) { return 2 * x; }
}  // namespace

TEST(Ex08_Lambdas, MapInPlaceWithAFunction) {
  auto ints = std::vector<int>{1, 2, 3, 4, 5};
  MapInPlace(ints, TimesTwo);
  EXPECT_EQ(ints, (std::vector<int>{2, 4, 6, 8, 10}));
}

TEST(Ex08_Lambdas, MapInPlaceWithALambda) {
  auto ints = std::vector<int>{1, 2, 3};
  MapInPlace(ints, [](int x) -> int { return x * x + 1; });
  EXPECT_EQ(ints, (std::vector<int>{2, 5, 10}));
}

TEST(Ex08_Lambdas, Filter) {
  auto evens = Filter({1, 2, 3, 4, 5, 6}, [](int x) { return x % 2 == 0; });
  EXPECT_EQ(evens, (std::vector<int>{2, 4, 6}));
  EXPECT_EQ(Filter({1, 3}, [](int x) { return x > 5; }), std::vector<int>{});
}

TEST(Ex08_Lambdas, MakeMultiplierWorksAfterItReturns) {
  auto triple = MakeMultiplier(3);
  auto negate = MakeMultiplier(-1);
  EXPECT_EQ(triple(5), 15);
  EXPECT_EQ(negate(5), -5);
  EXPECT_EQ(triple(-2), -6) << "Each returned function keeps its own copy of factor";
}

TEST(Ex08_Lambdas, Compose) {
  auto add_one = [](int x) { return x + 1; };
  auto f = Compose(add_one, TimesTwo);   // add_one(TimesTwo(x))
  auto g = Compose(TimesTwo, add_one);   // TimesTwo(add_one(x))
  EXPECT_EQ(f(5), 11);
  EXPECT_EQ(g(5), 12);
}

TEST(Ex08_Lambdas, ApplyN) {
  EXPECT_EQ(ApplyN(TimesTwo, 3, 1), 8);
  EXPECT_EQ(ApplyN(TimesTwo, 0, 7), 7);
  EXPECT_EQ(ApplyN([](int x) { return x - 3; }, 2, 10), 4);
}

TEST(Ex08_Lambdas, MakeAddersEachRememberTheirOwnI) {
  auto adders = MakeAdders(4);
  ASSERT_EQ(adders.size(), 4u);
  EXPECT_EQ(adders[0](10), 10);
  EXPECT_EQ(adders[1](10), 11);
  EXPECT_EQ(adders[3](10), 13)
      << "Capture the loop variable by value - by reference, every lambda would refer "
         "to the same (and soon dead) variable";
}

TEST(Ex08_Capture, SumUsingForEach) {
  EXPECT_EQ(SumUsingForEach({1, 2, 3, 4}), 10)
      << "The lambda must capture the running total by reference to update it";
  EXPECT_EQ(SumUsingForEach({}), 0);
}

TEST(Ex08_Capture, CountAboveUsingForEach) {
  EXPECT_EQ(CountAboveUsingForEach({1, 5, 10, 15}, 5), 2);
  EXPECT_EQ(CountAboveUsingForEach({1, 2}, 100), 0);
}
