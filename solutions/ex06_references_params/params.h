// Exercise 6 - model solution.
#pragma once

#include <cstddef>
#include <string>
#include <vector>

// Required + modified -> references.
void Swap(int& a, int& b);
void IncrementAll(std::vector<int>& values);

// Required + not modified + expensive -> const reference.
std::size_t CountVowels(const std::string& text);

// Required + not modified + cheap -> value.
int Square(int x);

// Optional + not modified -> const pointer.
int ClampTo(int value, const int* max_value);

// text: required, read-only, expensive -> const reference.
// out: optional + modified -> pointer.
bool ParseDigits(const std::string& text, int* out);

// Must be a reference: with a by-value parameter the function would return a
// pointer into its own local copy, which dies when the function returns.
const std::string* FindLongest(const std::vector<std::string>& words);
