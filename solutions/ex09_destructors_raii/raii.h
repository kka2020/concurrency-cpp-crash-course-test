// Exercise 9: object lifetime and destructors
//
// Concepts: a stack object lives from its declaration to the end of its scope;
// objects in the same scope are destroyed in REVERSE order of declaration;
// fields are constructed in declaration order and destroyed in reverse, AFTER
// the destructor body of the object that contains them.
//
// Implement the classes and function in raii.cc.
//
// Tests: tests/test_ex09_destructors_raii.cpp
// Run configuration: ex09_destructors_raii_test
#pragma once

#include <string>
#include <vector>

// Appends "enter <name>" to `log` when constructed, and "exit <name>" to the same
// log when destroyed.
class ScopedLogger {
 public:
  ScopedLogger(std::string name, std::vector<std::string>& log);
  ~ScopedLogger();

 private:
  std::string name_;
  std::vector<std::string>& log_;  // A reference member: must be set in the initializer list.
};

// A Pipeline owns two ScopedLogger fields, named "source" and "sink".
// Its constructor BODY appends "pipeline ready" to the log, and its destructor
// BODY appends "pipeline done".
// (Work out what the complete log of creating and destroying a Pipeline will be
// before you look at the test.)
class Pipeline {
 public:
  explicit Pipeline(std::vector<std::string>& log);
  ~Pipeline();

 private:
  std::vector<std::string>& log_;
  ScopedLogger source_;
  ScopedLogger sink_;
};

// Using ONLY ScopedLogger objects and { } blocks - no direct log.push_back - make
// RunScopes append exactly this sequence to `log`:
//
//   enter main
//   enter setup
//   exit setup
//   enter work
//   enter step1
//   enter step2
//   exit step2
//   exit step1
//   exit work
//   enter cleanup
//   exit cleanup
//   exit main
//
// Rule: at most ONE pair of { } braces inside the function body (besides the
// function's own braces). Think about what declaration order alone can achieve.
void RunScopes(std::vector<std::string>& log);
