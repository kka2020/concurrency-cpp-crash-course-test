// Exercise 4 - model solution. Each fix is marked FIX.
#pragma once

#include <string>
#include <vector>

// Bug 1: Sound() was not virtual, so Dog::Sound HID Animal::Sound instead of
// overriding it. Speak() (an Animal method) therefore always called Animal::Sound.
class Animal {
 public:
  virtual ~Animal() = default;
  virtual std::string Sound() const { return "..."; }  // FIX: virtual
  std::string Speak() const { return "The animal says " + Sound(); }
};

class Dog : public Animal {
 public:
  std::string Sound() const override { return "Woof"; }  // FIX: override (documents intent)
};

void ExclaimAll(std::vector<std::string>& words);

int CountMatching(const std::vector<int>& values, int target);

inline int g_connections_closed = 0;

// Bug 4: deleting a Connection through a Resource pointer (which is what
// std::unique_ptr<Resource> does) needs a virtual destructor in Resource.
class Resource {
 public:
  virtual ~Resource() { }  // FIX: virtual
};

class Connection : public Resource {
 public:
  ~Connection() { g_connections_closed++; }
};

void ApplyBonus(std::vector<int>& scores, int bonus);  // FIX: & (see bugs.cc)

struct Player {
  std::string name;
  int score;
};

void RewardFirstPlayer(std::vector<Player>& players, int points);
