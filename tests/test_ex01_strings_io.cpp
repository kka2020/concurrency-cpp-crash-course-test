// Tests for Exercise 1. Don't edit - make them pass by editing strings_io.cc.
#include <gtest/gtest.h>

#include <sstream>

#include "strings_io.h"

TEST(Ex01_Strings, JoinArgsSkipsProgramName) {
  char prog[] = "prog", a[] = "alpha", b[] = "beta", c[] = "gamma";
  char* argv[] = {prog, a, b, c};
  EXPECT_EQ(JoinArgs(4, argv, ", "), "alpha, beta, gamma")
      << "argv[0] is the program name and must not be included";
}

TEST(Ex01_Strings, JoinArgsSingleArgumentHasNoSeparator) {
  char prog[] = "prog", a[] = "alpha";
  char* argv[] = {prog, a};
  EXPECT_EQ(JoinArgs(2, argv, "--"), "alpha");
}

TEST(Ex01_Strings, JoinArgsWithNoArgumentsIsEmpty) {
  char prog[] = "prog";
  char* argv[] = {prog};
  EXPECT_EQ(JoinArgs(1, argv, ", "), "");
}

TEST(Ex01_Strings, RepeatConcatenates) {
  EXPECT_EQ(Repeat("ab", 3), "ababab");
  EXPECT_EQ(Repeat("x", 1), "x");
}

TEST(Ex01_Strings, RepeatZeroOrNegativeTimesIsEmpty) {
  EXPECT_EQ(Repeat("ab", 0), "");
  EXPECT_EQ(Repeat("ab", -2), "");
}

TEST(Ex01_Strings, ShoutModifiesCallersString) {
  std::string s = "hi";
  Shout(s);
  Shout(s);
  EXPECT_EQ(s, "hi!!") << "std::string is mutable: append changes the string in place";
}

TEST(Ex01_Strings, DescribeBuildsSentence) {
  EXPECT_EQ(Describe("Ada", 36), "Ada is 36 years old");
  EXPECT_EQ(Describe("Bjarne", 0), "Bjarne is 0 years old");
}

TEST(Ex01_Streams, PrintReportSendsValuesToOutAndErrorsToErr) {
  std::ostringstream out;
  std::ostringstream err;
  PrintReport(out, err, {3, -1, 0, -20});
  EXPECT_EQ(out.str(), "value: 3\nvalue: 0\n");
  EXPECT_EQ(err.str(), "error: negative value -1\nerror: negative value -20\n");
}

TEST(Ex01_Streams, PrintReportWithNoValuesWritesNothing) {
  std::ostringstream out;
  std::ostringstream err;
  PrintReport(out, err, {});
  EXPECT_EQ(out.str(), "");
  EXPECT_EQ(err.str(), "");
}
