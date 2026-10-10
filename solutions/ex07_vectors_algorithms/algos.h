// Exercise 7: std::vector, iterators, <algorithm> and auto
//
// Concepts: push_back, size, erase, std::find (returns end() when not found),
// iterators, range-based for loops by value vs by reference, auto.
// Bonus: std::map, from the "Sets and maps - check these out" slide.
//
// Use std::find where it fits, and prefer `auto` for iterator types.
// Implement the functions in algos.cc.
//
// Tests: tests/test_ex07_vectors_algorithms.cpp
// Run configuration: ex07_vectors_algorithms_test
#pragma once

#include <map>
#include <string>
#include <vector>

// True if `word` occurs in `words`. Use std::find.
bool Contains(const std::vector<std::string>& words, const std::string& word);

// Index of the first occurrence of `target`, or -1 if absent.
// Hint: for an iterator `it` into `values`, (it - values.begin()) is its index.
int IndexOf(const std::vector<int>& values, int target);

// Removes the FIRST occurrence of `word`. Returns true if something was removed,
// false (leaving `words` untouched) if `word` was not there.
bool RemoveFirst(std::vector<std::string>& words, const std::string& word);

// Removes EVERY occurrence of `target`.
void RemoveAll(std::vector<int>& values, int target);

// Appends `suffix` to every word in place.
void AppendToAll(std::vector<std::string>& words, const std::string& suffix);

// Returns a new vector with duplicates removed, keeping the first occurrence of
// each value, in the original order: {3, 1, 3, 2, 1} -> {3, 1, 2}.
std::vector<int> UniqueInOrder(const std::vector<int>& values);

// Bonus: maps each distinct word to how many times it occurs.
std::map<std::string, int> CountOccurrences(const std::vector<std::string>& words);
