#include "lambdas.h"

#include <stdexcept>

// TODO: replace each `throw` with a real implementation.

void MapInPlace(std::vector<int>& data, const std::function<int(int)>& fn) {
  throw std::logic_error("TODO: implement MapInPlace");
}

std::vector<int> Filter(const std::vector<int>& data, const std::function<bool(int)>& keep) {
  throw std::logic_error("TODO: implement Filter");
}

std::function<int(int)> MakeMultiplier(int factor) {
  throw std::logic_error("TODO: implement MakeMultiplier");
}

std::function<int(int)> Compose(std::function<int(int)> f, std::function<int(int)> g) {
  throw std::logic_error("TODO: implement Compose");
}

int ApplyN(const std::function<int(int)>& fn, int n, int x) {
  throw std::logic_error("TODO: implement ApplyN");
}

std::vector<std::function<int(int)>> MakeAdders(int n) {
  throw std::logic_error("TODO: implement MakeAdders");
}

void ForEach(const std::vector<int>& data, const std::function<void(int)>& visit) {
  for (int element : data) {
    visit(element);
  }
}

int SumUsingForEach(const std::vector<int>& data) {
  throw std::logic_error("TODO: implement SumUsingForEach");
}

int CountAboveUsingForEach(const std::vector<int>& data, int threshold) {
  throw std::logic_error("TODO: implement CountAboveUsingForEach");
}
