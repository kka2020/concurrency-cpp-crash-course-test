#include "params.h"

#include <cctype>

void Swap(int& a, int& b) {
  int tmp = a;
  a = b;
  b = tmp;
}

void IncrementAll(std::vector<int>& values) {
  for (auto& value : values) {
    value++;
  }
}

std::size_t CountVowels(const std::string& text) {
  std::size_t count = 0;
  for (char c : text) {
    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') {
      count++;
    }
  }
  return count;
}

int Square(int x) {
  return x * x;
}

int ClampTo(int value, const int* max_value) {
  if (max_value != nullptr && value > *max_value) {
    return *max_value;
  }
  return value;
}

bool ParseDigits(const std::string& text, int* out) {
  if (text.empty()) {
    return false;
  }
  int result = 0;
  for (char c : text) {
    if (c < '0' || c > '9') {
      return false;
    }
    result = result * 10 + (c - '0');
  }
  if (out != nullptr) {
    *out = result;
  }
  return true;
}

const std::string* FindLongest(const std::vector<std::string>& words) {
  const std::string* longest = nullptr;
  for (const auto& word : words) {
    if (longest == nullptr || word.size() > longest->size()) {
      longest = &word;
    }
  }
  return longest;
}
