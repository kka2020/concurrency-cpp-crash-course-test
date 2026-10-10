// Exercise 8: function objects and lambdas
//
// Concepts: std::function, passing functions and lambdas as arguments,
// returning lambdas, capture by value [x] vs capture by reference [&x].
//
// Implement the functions in lambdas.cc. ForEach is already done for you.
//
// Tests: tests/test_ex08_lambdas.cpp    Run configuration: ex08_lambdas_test
#pragma once

#include <functional>
#include <vector>

// Replaces every element x with fn(x) (the crash course's MapInPlace).
void MapInPlace(std::vector<int>& data, const std::function<int(int)>& fn);

// Returns the elements for which keep(element) is true, in their original order.
std::vector<int> Filter(const std::vector<int>& data, const std::function<bool(int)>& keep);

// Returns a function that multiplies its argument by `factor`.
// Think about the capture: the returned function outlives this call.
std::function<int(int)> MakeMultiplier(int factor);

// Returns the function x -> f(g(x)).
std::function<int(int)> Compose(std::function<int(int)> f, std::function<int(int)> g);

// Applies fn to x, n times: ApplyN(fn, 3, x) == fn(fn(fn(x))). ApplyN(fn, 0, x) == x.
int ApplyN(const std::function<int(int)>& fn, int n, int x);

// Returns n functions; the i-th one (counting from 0) adds i to its argument:
//   MakeAdders(3)[2](10) == 12
std::vector<std::function<int(int)>> MakeAdders(int n);

// Calls visit(element) for every element. Already implemented.
void ForEach(const std::vector<int>& data, const std::function<void(int)>& visit);

// Implement these two by calling ForEach with a lambda that updates a local
// variable of the enclosing function (no loops of your own!).
int SumUsingForEach(const std::vector<int>& data);
int CountAboveUsingForEach(const std::vector<int>& data, int threshold);
