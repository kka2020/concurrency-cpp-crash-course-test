#include "raii.h"

#include <stdexcept>

// TODO: implement everything below.
// (Destructors must not throw, so the destructor stubs are simply empty.)

ScopedLogger::ScopedLogger(std::string name, std::vector<std::string>& log)
    : name_(name), log_(log) {
  // TODO
}

ScopedLogger::~ScopedLogger() {
  // TODO
}

// TODO: ScopedLogger has no default constructor, so Pipeline's constructor must
// construct source_ and sink_ explicitly. Fix the initializer list.
Pipeline::Pipeline(std::vector<std::string>& log)
    : log_(log), source_("TODO", log), sink_("TODO", log) {
  // TODO
}

Pipeline::~Pipeline() {
  // TODO
}

void RunScopes(std::vector<std::string>& log) {
  throw std::logic_error("TODO: implement RunScopes");
}
