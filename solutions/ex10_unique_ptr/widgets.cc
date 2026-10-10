#include "widgets.h"

std::unique_ptr<Widget> MakeWidget(const std::string& name, bool fancy) {
  if (fancy) {
    return std::make_unique<FancyWidget>(name);
  }
  return std::make_unique<Widget>(name);
}

std::string Inspect(const Widget* w) {
  if (w == nullptr) {
    return "nothing";
  }
  return w->Name() + " (" + w->Kind() + ")";
}

std::string Consume(std::unique_ptr<Widget> w) {
  return w->Name();
}  // w goes out of scope here, destroying the widget.

std::unique_ptr<Widget> TakeLongestNamed(std::vector<std::unique_ptr<Widget>>& widgets) {
  if (widgets.empty()) {
    return nullptr;
  }
  auto longest = widgets.begin();
  for (auto it = widgets.begin(); it != widgets.end(); ++it) {
    if ((*it)->Name().size() > (*longest)->Name().size()) {
      longest = it;
    }
  }
  std::unique_ptr<Widget> taken = std::move(*longest);  // Vector slot is now empty...
  widgets.erase(longest);                               // ...so remove it.
  return taken;
}
