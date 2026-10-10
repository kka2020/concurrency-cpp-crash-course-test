// Exercise 1: strings and console output
//
// Concepts: std::string (mutable, append, +), std::to_string, output streams
// (std::cout and std::cerr are both std::ostream objects), std::endl.
//
// Implement the functions declared below in strings_io.cc.
// Tests: tests/test_ex01_strings_io.cpp    Run configuration: ex01_strings_io_test
#pragma once

#include <ostream>
#include <string>
#include <vector>

// Joins argv[1] .. argv[argc - 1] (NOT the program name argv[0]) with `separator`
// between consecutive arguments:
//   argv = {"prog", "a", "b"}, argc = 3, separator ", "  ->  "a, b"
// Returns "" if there are no arguments after the program name.
std::string JoinArgs(int argc, char** argv, const std::string& separator);

// Returns `text` repeated `times` times: Repeat("ab", 3) == "ababab".
// Returns "" if times <= 0.
std::string Repeat(const std::string& text, int times);

// Appends "!" to `text` IN PLACE - the caller's string must change.
void Shout(std::string& text);

// Returns "<name> is <age> years old", e.g. Describe("Ada", 36) == "Ada is 36 years old".
std::string Describe(const std::string& name, int age);

// For each value, in order:
//   value >= 0: write "value: <value>" and a newline to `out`
//   value <  0: write "error: negative value <value>" and a newline to `err`
// In a real program you'd pass std::cout and std::cerr. The tests pass string
// streams instead, so they can check exactly what you wrote.
void PrintReport(std::ostream& out, std::ostream& err, const std::vector<int>& values);
