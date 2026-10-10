#include "strings_io.h"

std::string JoinArgs(int argc, char** argv, const std::string& separator) {
  std::string result;
  for (int i = 1; i < argc; i++) {
    if (i > 1) {
      result.append(separator);
    }
    result.append(argv[i]);
  }
  return result;
}

std::string Repeat(const std::string& text, int times) {
  std::string result;
  for (int i = 0; i < times; i++) {
    result.append(text);
  }
  return result;
}

void Shout(std::string& text) {
  text.append("!");
}

std::string Describe(const std::string& name, int age) {
  return name + " is " + std::to_string(age) + " years old";
}

void PrintReport(std::ostream& out, std::ostream& err, const std::vector<int>& values) {
  for (int value : values) {
    if (value >= 0) {
      out << "value: " << value << std::endl;
    } else {
      err << "error: negative value " << value << std::endl;
    }
  }
}
