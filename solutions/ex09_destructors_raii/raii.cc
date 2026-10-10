#include "raii.h"

ScopedLogger::ScopedLogger(std::string name, std::vector<std::string>& log)
    : name_(name), log_(log) {
  log_.push_back("enter " + name_);
}

ScopedLogger::~ScopedLogger() {
  log_.push_back("exit " + name_);
}

// Fields are constructed in DECLARATION order (log_, source_, sink_) before the
// constructor body runs. On destruction the body runs first, then the fields are
// destroyed in reverse order (sink_, then source_).
Pipeline::Pipeline(std::vector<std::string>& log)
    : log_(log), source_("source", log), sink_("sink", log) {
  log_.push_back("pipeline ready");
}

Pipeline::~Pipeline() {
  log_.push_back("pipeline done");
}

void RunScopes(std::vector<std::string>& log) {
  ScopedLogger main_logger("main", log);
  // A temporary (unnamed) object is destroyed at the end of the full expression -
  // just like the A(i) temporaries passed to push_back in the crash course.
  ScopedLogger("setup", log);
  {
    ScopedLogger work("work", log);
    ScopedLogger step1("step1", log);
    ScopedLogger step2("step2", log);
  }  // step2, step1, work destroyed here, in reverse order of declaration.
  ScopedLogger cleanup("cleanup", log);
}  // cleanup, then main_logger.
