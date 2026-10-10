#include "algos.h"

#include <algorithm>

bool Contains(const std::vector<std::string>& words, const std::string& word) {
  return std::find(words.begin(), words.end(), word) != words.end();
}

int IndexOf(const std::vector<int>& values, int target) {
  auto it = std::find(values.begin(), values.end(), target);
  if (it == values.end()) {
    return -1;
  }
  return static_cast<int>(it - values.begin());
}

bool RemoveFirst(std::vector<std::string>& words, const std::string& word) {
  auto it = std::find(words.begin(), words.end(), word);
  if (it == words.end()) {
    return false;  // Erasing end() would be undefined behaviour.
  }
  words.erase(it);
  return true;
}

void RemoveAll(std::vector<int>& values, int target) {
  auto it = std::find(values.begin(), values.end(), target);
  while (it != values.end()) {
    // erase returns an iterator to the element after the erased one, so the
    // search can continue from there.
    it = std::find(values.erase(it), values.end(), target);
  }
}

void AppendToAll(std::vector<std::string>& words, const std::string& suffix) {
  for (auto& word : words) {  // By reference, or we'd modify copies.
    word.append(suffix);
  }
}

std::vector<int> UniqueInOrder(const std::vector<int>& values) {
  std::vector<int> result;
  for (int value : values) {
    if (std::find(result.begin(), result.end(), value) == result.end()) {
      result.push_back(value);
    }
  }
  return result;
}

std::map<std::string, int> CountOccurrences(const std::vector<std::string>& words) {
  std::map<std::string, int> counts;
  for (const auto& word : words) {
    counts[word]++;  // operator[] inserts 0 for a missing key first.
  }
  return counts;
}
