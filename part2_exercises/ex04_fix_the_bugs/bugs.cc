#include "bugs.h"

// Bug 2
void ExclaimAll(std::vector<std::string>& words) {
  for (std::string word : words) {
    word.append("!");
  }
}

// Bug 3
// (`mutable` lets a lambda modify the variables it captured by value.)
int CountMatching(const std::vector<int>& values, int target) {
  int count = 0;
  auto count_one = [count]() mutable { count++; };
  for (int value : values) {
    if (value == target) {
      count_one();
    }
  }
  return count;
}

// Bug 5
void ApplyBonus(std::vector<int> scores, int bonus) {
  for (auto& score : scores) {
    score += bonus;
  }
}

// Bug 6
void RewardFirstPlayer(std::vector<Player>& players, int points) {
  if (players.empty()) {
    return;
  }
  auto first = players[0];
  first.score += points;
}
