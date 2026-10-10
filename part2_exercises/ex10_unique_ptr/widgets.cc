#include "widgets.h"

#include <stdexcept>

// TODO: replace each `throw` with a real implementation.

std::unique_ptr<Widget> MakeWidget(const std::string& name, bool fancy) {
  throw std::logic_error("TODO: implement MakeWidget");
}

std::string Inspect(const Widget* w) {
  throw std::logic_error("TODO: implement Inspect");
}

std::string Consume(std::unique_ptr<Widget> w) {
  throw std::logic_error("TODO: implement Consume");
}

std::unique_ptr<Widget> TakeLongestNamed(std::vector<std::unique_ptr<Widget>>& widgets) {
  throw std::logic_error("TODO: implement TakeLongestNamed");
}
