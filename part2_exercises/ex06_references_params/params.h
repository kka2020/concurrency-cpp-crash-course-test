// Exercise 6: references, pointers and the parameter-passing cheat sheet
//
// The function SIGNATURES below were written by someone who ignored the cheat
// sheet. Some are plainly broken (the function can't do its job); others work but
// are wasteful or misleading. Fix every PARAMETER type (here AND in params.cc) so
// it follows the cheat sheet exactly, then implement the functions.
//
//   Parameter is...                                      Use
//   required, not modified, cheap to copy                value         T
//   required, not modified, expensive to copy            const ref     const T&
//   required, modified by the function                   reference     T&
//   optional (may be nullptr), not modified              const ptr     const T*
//   optional (may be nullptr), modified by the function  pointer       T*
//
// Treat int as cheap to copy, and std::string / std::vector as expensive.
// Return types are already correct. The tests check behaviour AND signatures.
//
// Tests: tests/test_ex06_references_params.cpp
// Run configuration: ex06_references_params_test
#pragma once

#include <cstddef>
#include <string>
#include <vector>

// Swaps the values of the caller's two variables.
void Swap(int a, int b);

// Adds 1 to every element of the caller's vector.
void IncrementAll(std::vector<int> values);

// Number of vowels (a, e, i, o, u - upper or lower case) in `text`.
std::size_t CountVowels(std::string text);

// Returns x * x.
int Square(const int& x);

// Returns `value`, but no larger than *max_value when max_value is provided
// (non-null). ClampTo(7, nullptr) == 7.
int ClampTo(int value, int* max_value);

// Parses a non-empty string made only of decimal digits ("0042" -> 42) and
// returns true. Returns false for anything else ("", "-1", "4a", " 4").
// On success, also stores the number in *out - unless out is nullptr, in which
// case the caller only wanted to validate the text. On failure *out is unchanged.
bool ParseDigits(std::string text, const int* out);

// Returns a pointer to the longest string in `words` (the earliest one if there
// is a tie), or nullptr if `words` is empty. The pointer must point INTO the
// caller's vector.
const std::string* FindLongest(std::vector<std::string> words);
