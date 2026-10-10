#include "lambdas.h"

void MapInPlace(std::vector<int>& data, const std::function<int(int)>& fn) {
  for (auto& elem : data) {
    elem = fn(elem);
  }
}

std::vector<int> Filter(const std::vector<int>& data, const std::function<bool(int)>& keep) {
  std::vector<int> result;
  for (int elem : data) {
    if (keep(elem)) {
      result.push_back(elem);
    }
  }
  return result;
}

std::function<int(int)> MakeMultiplier(int factor) {
  // By value: `factor` is a parameter that dies when MakeMultiplier returns, so
  // capturing it by reference would leave the lambda with a dangling reference.
  return [factor](int x) -> int { return factor * x; };
}

std::function<int(int)> Compose(std::function<int(int)> f, std::function<int(int)> g) {
  return [f, g](int x) -> int { return f(g(x)); };
}

int ApplyN(const std::function<int(int)>& fn, int n, int x) {
  for (int i = 0; i < n; i++) {
    x = fn(x);
  }
  return x;
}

std::vector<std::function<int(int)>> MakeAdders(int n) {
  std::vector<std::function<int(int)>> adders;
  for (int i = 0; i < n; i++) {
    // [i] copies the CURRENT value of i into each lambda.
    adders.push_back([i](int x) -> int { return x + i; });
  }
  return adders;
}

void ForEach(const std::vector<int>& data, const std::function<void(int)>& visit) {
  for (int element : data) {
    visit(element);
  }
}

int SumUsingForEach(const std::vector<int>& data) {
  int total = 0;
  ForEach(data, [&total](int x) { total += x; });
  return total;
}

int CountAboveUsingForEach(const std::vector<int>& data, int threshold) {
  int count = 0;
  ForEach(data, [&count, threshold](int x) {
    if (x > threshold) {
      count++;
    }
  });
  return count;
}
