#include "bugs.h"

// Bug 2: `std::string word` iterated BY VALUE, so each append modified a copy.
void ExclaimAll(std::vector<std::string>& words) {
  for (std::string& word : words) {  // FIX: &
    word.append("!");
  }
}

// Bug 3: [count] captured a COPY of count; the lambda incremented its copy and
// the local count stayed 0. Capture by reference instead (and drop mutable).
int CountMatching(const std::vector<int>& values, int target) {
  int count = 0;
  auto count_one = [&count]() { count++; };  // FIX: &count
  for (int value : values) {
    if (value == target) {
      count_one();
    }
  }
  return count;
}

// Bug 5: the vector was passed BY VALUE, so the function modified a copy.
// Required + modified => pass by reference.
void ApplyBonus(std::vector<int>& scores, int bonus) {  // FIX: &
  for (auto& score : scores) {
    score += bonus;
  }
}

// Bug 6: plain `auto` deduces Player, i.e. a COPY of players[0].
void RewardFirstPlayer(std::vector<Player>& players, int points) {
  if (players.empty()) {
    return;
  }
  auto& first = players[0];  // FIX: auto&
  first.score += points;
}
