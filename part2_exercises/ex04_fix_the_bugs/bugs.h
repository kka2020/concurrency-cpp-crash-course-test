// Exercise 4: find and fix the bugs
//
// Everything below COMPILES and LOOKS reasonable, but each numbered section has
// exactly one bug - a classic crash-course "gotcha". The tests describe the
// intended behaviour. Fix the code here and in bugs.cc (don't edit the tests).
//
// Every fix is tiny: usually one keyword or one character. If you find yourself
// rewriting a function, look again.
//
// Tests: tests/test_ex04_fix_the_bugs.cpp    Run configuration: ex04_fix_the_bugs_test
#pragma once

#include <string>
#include <vector>

// Bug 1 ----------------------------------------------------------------------
// Every animal can Speak(); a Dog should say "The animal says Woof".
class Animal {
 public:
  virtual ~Animal() = default;
  std::string Sound() const { return "..."; }
  std::string Speak() const { return "The animal says " + Sound(); }
};

class Dog : public Animal {
 public:
  std::string Sound() const { return "Woof"; }
};

// Bug 2 ----------------------------------------------------------------------
// Appends "!" to every word in `words`.
void ExclaimAll(std::vector<std::string>& words);

// Bug 3 ----------------------------------------------------------------------
// Returns how many elements of `values` are equal to `target`.
int CountMatching(const std::vector<int>& values, int target);

// Bug 4 ----------------------------------------------------------------------
// Connections are handed around as std::unique_ptr<Resource>. Every Connection
// that is destroyed must be counted in g_connections_closed.
inline int g_connections_closed = 0;

class Resource {
 public:
  ~Resource() { }
};

class Connection : public Resource {
 public:
  ~Connection() { g_connections_closed++; }
};

// Bug 5 ----------------------------------------------------------------------
// Adds `bonus` to every score.
void ApplyBonus(std::vector<int> scores, int bonus);

// Bug 6 ----------------------------------------------------------------------
struct Player {
  std::string name;
  int score;
};

// Gives the first player in the list `points` extra points (does nothing if
// the list is empty).
void RewardFirstPlayer(std::vector<Player>& players, int points);
