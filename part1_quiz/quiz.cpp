// Part 1: interactive concept quiz for the C++ crash course.
//
// Run the "1_quiz" configuration in CLion and type your answers in the Run
// console. Don't read the question data below before taking the quiz - the
// answers are in it!

#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace {

enum class Kind { kChoice, kOutput };

struct Question {
  std::string topic;
  Kind kind;
  std::string prompt;
  std::string code;                  // May be empty.
  std::vector<std::string> options;  // kChoice only.
  std::string answer;                // kChoice: a letter. kOutput: the expected output.
  std::string explanation;
};

const std::vector<std::string>& TopicOrder() {
  static const std::vector<std::string> topics = {
      "Basics",         "Classes",       "Inheritance", "Abstract classes",
      "Templates",      "References",    "Vectors",     "Lambdas",
      "Destructors",    "Smart pointers"};
  return topics;
}

const std::vector<Question>& AllQuestions() {
  static const std::vector<Question> questions = {
      // ------------------------------------------------------------------ Basics
      {"Basics", Kind::kChoice,
       "What is the difference between these two lines?",
       R"cpp(std::cout << x << std::endl;
std::cout << x << '\n';)cpp",
       {"There is no difference at all",
        "std::endl also flushes the output buffer",
        "std::endl writes to standard error instead of standard output",
        "'\\n' cannot be used with std::cout"},
       "B",
       "std::endl writes '\\n' AND flushes the stream's buffer. Standard error is "
       "std::cerr, a different stream."},

      {"Basics", Kind::kOutput, "What does this print?",
       R"cpp(std::string s("ab");
s.append("cd");
s.append(s);
print(s);
print(s.size());)cpp",
       {}, "abcdabcd 8",
       "std::string is mutable (unlike Java's String): append changes s in place. "
       "s.append(s) appends a copy of the current contents, giving \"abcdabcd\" (8 chars)."},

      // ----------------------------------------------------------------- Classes
      {"Classes", Kind::kChoice, "Which marked line fails to compile?",
       R"cpp(class Counter {
 public:
  explicit Counter(int start) : count_(start) { }
  int Get() const { return count_; }                  // (1)
  void Increment() { count_++; }                      // (2)
  int GetAndIncrement() const { return count_++; }    // (3)
 private:
  int count_;
};)cpp",
       {"(1)", "(2)", "(3)", "They all compile"},
       "C",
       "A const method promises not to modify the object's state, so (3) cannot do "
       "count_++. (1) only reads, and (2) is not const so it may modify count_."},

      {"Classes", Kind::kChoice, "Which marked lines compile?",
       R"cpp(struct P { int x; };
class Q { int x; };

int main() {
  P p; p.x = 1;   // (1)
  Q q; q.x = 1;   // (2)
})cpp",
       {"Both", "Only (1)", "Only (2)", "Neither"},
       "B",
       "struct and class are the same except for default access: struct members are "
       "public by default, class members are private by default."},

      {"Classes", Kind::kChoice,
       "A.h declares the class below. Which is a correct definition of GetX in A.cc?",
       R"cpp(class A {
 public:
  int GetX() const;
 private:
  int x_;
};)cpp",
       {"int GetX() const { return x_; }", "int A::GetX() const { return x_; }",
        "int A::GetX() { return x_; }", "A::int GetX() const { return x_; }"},
       "B",
       "Out-of-class definitions use A::Name to say which class the method belongs to. "
       "The const is part of the signature, so (C) would not match the declaration, and "
       "(A) defines an unrelated free function."},

      {"Classes", Kind::kChoice, "Which marked lines compile?",
       R"cpp(class Meters {
 public:
  explicit Meters(double value) : value_(value) { }
 private:
  double value_;
};
void Run(Meters distance);

Run(Meters(5.0));   // (1)
Run(5.0);           // (2)
Meters m = 5.0;     // (3))cpp",
       {"All three", "Only (1)", "(1) and (2)", "(1) and (3)"},
       "B",
       "explicit forbids implicit calls to a single-argument constructor, so (2) and (3) "
       "no longer silently convert a double into Meters. Without explicit, all three "
       "would compile."},

      // ------------------------------------------------------------- Inheritance
      {"Inheritance", Kind::kOutput, "What does this print?",
       R"cpp(class A {
 public:
  void Foo() { print("A::Foo"); }
};
class B : public A {
 public:
  void Foo() { print("B::Foo"); }
};
void DoIt(A* a) { a->Foo(); }

int main() {
  B b;
  b.Foo();
  DoIt(&b);
})cpp",
       {}, "B::Foo A::Foo",
       "Foo is not virtual, so B::Foo HIDES A::Foo rather than overriding it. Normal "
       "methods are dispatched on the apparent (static) type: inside DoIt that is A*, "
       "so A::Foo runs even though the object is really a B."},

      {"Inheritance", Kind::kOutput, "What does this print?",
       R"cpp(class A {
 public:
  virtual void Foo() { print("A::Foo"); }
  void Run() { print("A::Run"); Foo(); }
};
class B : public A {
 public:
  void Foo() override { A::Foo(); print("B::Foo"); }
};

int main() {
  B b;
  A& a = b;
  a.Run();
})cpp",
       {}, "A::Run A::Foo B::Foo",
       "Run is not virtual, so A::Run runs. Inside it, Foo() is virtual and dispatched "
       "on the actual type (B), so B::Foo runs, which first calls A::Foo explicitly."},

      {"Inheritance", Kind::kOutput, "What does this print?",
       R"cpp(class A {
 public:
  A(int x) : x_(x) { print("A(" + std::to_string(x) + ")"); }
  int x_;
};
class B : public A {
 public:
  B(int x, int y) : A(x), y_(y) { print("B(" + std::to_string(y) + ")"); }
  int y_;
};

int main() {
  B b(1, 2);
  print(b.x_ + b.y_);
})cpp",
       {}, "A(1) B(2) 3",
       "A(x) in B's initializer list is like Java's super(x): the base part is "
       "constructed first, then B's members, then B's constructor body runs."},

      {"Inheritance", Kind::kChoice, "What does the override keyword do?",
       "",
       {"It is required for dynamic dispatch to happen",
        "It states your intent; the compiler reports an error if the method does not "
        "actually override a virtual method",
        "It makes the method virtual in the base class",
        "It stops subclasses from overriding the method further"},
       "B",
       "Like Java's @Override, it is a safety check. Dynamic dispatch comes from the "
       "BASE method being virtual; override just makes the compiler confirm that it is."},

      // -------------------------------------------------------- Abstract classes
      {"Abstract classes", Kind::kChoice, "Which line compiles?",
       R"cpp(class Shape {
 public:
  virtual double Area() = 0;
  virtual void Print() { print("shape"); }
};)cpp",
       {"Shape s;", "Shape* p = nullptr;", "Shape s = Shape();", "None of them"},
       "B",
       "Area is pure virtual (= 0), so Shape is abstract and cannot be instantiated. "
       "Pointers (and references) to an abstract class are fine - that is how you use "
       "it polymorphically."},

      {"Abstract classes", Kind::kChoice, "A C++ class is abstract if and only if...",
       "",
       {"it is declared with the abstract keyword",
        "all of its methods are virtual",
        "it has at least one pure virtual (= 0) method",
        "it has no constructor"},
       "C",
       "There is no abstract (or interface) keyword in C++. One pure virtual method is "
       "enough. A class with only pure virtual methods is what people call an interface."},

      // --------------------------------------------------------------- Templates
      {"Templates", Kind::kChoice, "Which marked lines fail to compile?",
       R"cpp(template <typename T>
T Sub(T a, T b) { return a - b; }

Sub(5, 3);                                 // (1)
Sub(2.5, 1.0);                             // (2)
Sub(std::string("a"), std::string("b"));   // (3)
Sub(5, 2.0);                               // (4))cpp",
       {"Only (3)", "(3) and (4)", "Only (4)", "They all compile"},
       "B",
       "(3): the template assumes T has operator-, and std::string does not. "
       "(4): T is deduced as int from 5 and as double from 2.0 - a conflict, so "
       "deduction fails (you could write Sub<double>(5, 2.0))."},

      {"Templates", Kind::kOutput, "What does this print?",
       R"cpp(template <typename S, typename T>
class Pair {
 public:
  Pair(S first, T second) : first_(first), second_(second) { }
  S GetFirst() { return first_; }
  T GetSecond() { return second_; }
 private:
  S first_;
  T second_;
};

int main() {
  Pair p(7, 2.5);
  print(p.GetFirst() + p.GetSecond());
  Pair q(std::string("ab"), std::string("cd"));
  print(q.GetSecond() + q.GetFirst());
})cpp",
       {}, "9.5 cdab",
       "The compiler infers Pair<int, double> and Pair<std::string, std::string>. "
       "7 + 2.5 is 9.5, and + on strings concatenates."},

      {"Templates", Kind::kChoice, "Why doesn't this compile, and how do you fix it?",
       R"cpp(template <typename T>
class A {
 public:
  void Foo() { }
};
template <typename T>
class B : public A<T> {
 public:
  void Bar() { Foo(); }
};)cpp",
       {"It does compile",
        "The compiler won't look up Foo in the templated base A<T>; write this->Foo()",
        "A::Foo must be declared virtual",
        "You cannot inherit from a class template"},
       "B",
       "Because the base class depends on T, the compiler doesn't know that Foo refers "
       "to A<T>::Foo. this->Foo() resolves the ambiguity. (Without templates, Foo() "
       "would be fine.)"},

      {"Templates", Kind::kChoice,
       "A program uses Pair<int, std::string>, Pair<std::string, std::string> and "
       "Pair<int, int>. How many compiled versions of Pair's code end up in the executable?",
       "",
       {"1, shared by all uses (like Java generics)", "3", "0 - templates are "
        "interpreted at run time", "2"},
       "B",
       "A template is compiled separately for every distinct combination of type "
       "arguments. Pros: fast, specialised code. Cons: bigger executables, scary errors."},

      // -------------------------------------------------------------- References
      {"References", Kind::kOutput, "What does this print?",
       R"cpp(void Foo(int a) { a = 10; }
void Bar(int* a) { *a += 5; }
void Baz(int& a) {
  int& b = a;
  b *= 2;
  a++;
}

int main() {
  int x = 1;
  Foo(x);  print(x);
  Bar(&x); print(x);
  Baz(x);  print(x);
})cpp",
       {}, "1 6 13",
       "Foo gets a copy, so x stays 1. Bar gets a pointer to x: 1 + 5 = 6. Baz gets a "
       "reference, and b is another reference to the same int: 6 * 2 = 12, then 13."},

      {"References", Kind::kChoice, "Which statement about references is TRUE?",
       "",
       {"A reference can be null",
        "References support pointer arithmetic",
        "Passing an int& lets the function modify the caller's variable",
        "You must write *r to read the value a reference r refers to"},
       "C",
       "A reference is like a pointer that cannot be null and has no arithmetic, and it "
       "is used with normal syntax (no * or ->)."},

      {"References", Kind::kChoice,
       "PrintInvoice(items) only READS a std::vector<LineItem> with thousands of "
       "elements, and the argument is always provided. Best parameter type?",
       "",
       {"std::vector<LineItem> items", "std::vector<LineItem>& items",
        "const std::vector<LineItem>& items", "const std::vector<LineItem>* items"},
       "C",
       "Required + not modified + expensive to copy => const reference. A plain value "
       "copies thousands of items; a non-const reference suggests it modifies them; a "
       "pointer suggests the argument is optional."},

      {"References", Kind::kChoice,
       "Parse(text, error_code) can optionally write an error code back to the caller. "
       "Callers who don't care pass nullptr. Best type for error_code?",
       "",
       {"int error_code", "int& error_code", "const int* error_code", "int* error_code"},
       "D",
       "Optional + modified by the function => (non-const) pointer. const int* would be "
       "optional but read-only; a reference can't be null."},

      // ----------------------------------------------------------------- Vectors
      {"Vectors", Kind::kOutput, "What does this print?",
       R"cpp(std::vector<std::string> ss{"a", "b", "c"};
for (auto s : ss) { s.append("1"); }
for (auto& s : ss) { s.append("2"); }
for (auto& s : ss) { print(s); })cpp",
       {}, "a2 b2 c2",
       "The first loop iterates BY VALUE: each s is a copy, so appending \"1\" has no "
       "effect on ss. The second loop iterates by reference and modifies the elements."},

      {"Vectors", Kind::kOutput, "What does this print?",
       R"cpp(std::vector<int> v{3, 1, 4, 1, 5};
v.erase(std::find(v.begin(), v.end(), 1));
print(v.size());
for (auto x : v) { print(x); })cpp",
       {}, "4 3 4 1 5",
       "std::find returns an iterator to the FIRST 1, and erase removes just that "
       "element."},

      {"Vectors", Kind::kChoice,
       "What's wrong with this code if 42 might not be in v?",
       R"cpp(auto it = std::find(v.begin(), v.end(), 42);
v.erase(it);)cpp",
       {"Nothing: erase ignores elements that aren't there",
        "find returns v.end() when not found, and erasing end() is undefined "
        "behaviour - check it != v.end() first",
        "find throws an exception when the element is missing",
        "find returns nullptr when the element is missing"},
       "B",
       "A result equal to v.end() means \"not found\". Always compare against end() "
       "before using the iterator."},

      {"Vectors", Kind::kOutput, "What does this print?",
       R"cpp(std::vector<std::string> names{"ada", "bob"};
auto first = names[0];
first.append("!");
auto& second = names[1];
second.append("?");
print(names[0] + " " + names[1]);)cpp",
       {}, "ada bob?",
       "auto on its own deduces a plain std::string, i.e. a COPY. You need auto& to get "
       "a reference into the vector."},

      // ----------------------------------------------------------------- Lambdas
      {"Lambdas", Kind::kOutput, "What does this print?",
       R"cpp(int factor = 2;
auto by_value = [factor](int x) { return factor * x; };
auto by_ref = [&factor](int x) { return factor * x; };
factor = 10;
print(by_value(3));
print(by_ref(3));)cpp",
       {}, "6 30",
       "[factor] copies factor when the lambda is created (2). [&factor] refers to the "
       "variable itself and sees the latest value (10)."},

      {"Lambdas", Kind::kOutput, "What does this print?",
       R"cpp(void MapInPlace(std::vector<int>& data, std::function<int(int)> fn) {
  for (auto& elem : data) { elem = fn(elem); }
}

int main() {
  auto ints = std::vector<int>{1, 2, 3};
  int factor = 2;
  auto mult = [factor](int x) -> int { return factor * x; };
  MapInPlace(ints, mult);
  factor = 5;
  MapInPlace(ints, mult);
  MapInPlace(ints, [&factor](int x) -> int { return x + factor; });
  for (auto e : ints) { print(e); }
})cpp",
       {}, "9 13 17",
       "mult captured factor by value (2), so both calls double: 1,2,3 -> 2,4,6 -> "
       "4,8,12. The last lambda captures by reference and sees 5: 9,13,17."},

      {"Lambdas", Kind::kChoice,
       "Which of these can be passed where a std::function<int(int)> is expected?",
       R"cpp(int TimesTwo(int x) { return 2 * x; }              // (1)
[](int x) -> int { return x + 1; }                   // (2)
[k](int x) -> int { return k * x; }                  // (3), k is a local int)cpp",
       {"Only (1)", "Only lambdas without captures: (2)", "All three",
        "Only the lambdas: (2) and (3)"},
       "C",
       "std::function<int(int)> holds ANY callable that takes an int and returns an "
       "int: plain functions and lambdas, with or without captures."},

      // ------------------------------------------------------------- Destructors
      {"Destructors", Kind::kOutput, "What does this print?",
       R"cpp(class A {
 public:
  A(int x) : x_(x) { }
  ~A() { print("~A(" + std::to_string(x_) + ")"); }
  int x_;
};
void Foo() {
  A a1(1);
  {
    A a2(2);
  }
  A a3(3);
}

int main() {
  A a0(0);
  Foo();
  {
    A a4(4);
  }
  print("end");
})cpp",
       {}, "~A(2) ~A(3) ~A(1) ~A(4) end ~A(0)",
       "A stack object is destroyed when it goes out of scope. a2 dies at the end of "
       "its block; at the end of Foo, a3 and a1 die in REVERSE order of declaration; "
       "a4 dies at the end of its block; a0 dies when main returns."},

      {"Destructors", Kind::kOutput, "What does this print?",
       R"cpp(class A {
 public:
  A(int x) : x_(x) { }
  ~A() { print("~A(" + std::to_string(x_) + ")"); }
  int x_;
};
class B {
 public:
  B() : first_(1), second_(2) { print("B()"); }
  ~B() { print("~B()"); }
 private:
  A first_;
  A second_;
};

int main() {
  B b;
})cpp",
       {}, "B() ~B() ~A(2) ~A(1)",
       "B's destructor body runs first, then the destructors of its fields, in reverse "
       "order of declaration."},

      // ---------------------------------------------------------- Smart pointers
      {"Smart pointers", Kind::kChoice, "What is the problem with this program?",
       R"cpp(class Base {
 public:
  ~Base() { print("~Base"); }
};
class Derived : public Base {
 public:
  ~Derived() { print("~Derived"); }
};

int main() {
  std::unique_ptr<Base> p = std::make_unique<Derived>();
})cpp",
       {"None: it prints ~Derived then ~Base",
        "Base needs a virtual destructor: deleting a Derived through a Base pointer "
        "without one is undefined behaviour (typically ~Derived is skipped)",
        "std::make_unique cannot create a subclass",
        "A std::unique_ptr<Base> cannot hold a Derived"},
       "B",
       "A virtual destructor is required if a subclass instance will be deleted via a "
       "superclass pointer - which is exactly what unique_ptr<Base> does."},

      {"Smart pointers", Kind::kOutput, "What does this print?",
       R"cpp(class Base {
 public:
  virtual ~Base() { print("~Base"); }
};
class Derived : public Base {
 public:
  ~Derived() { print("~Derived"); }
};
void Take(std::unique_ptr<Base> p) { print("in Take"); }

int main() {
  std::unique_ptr<Base> owner = std::make_unique<Derived>();
  Take(std::move(owner));
  print(owner == nullptr ? "empty" : "full");
  print("end");
})cpp",
       {}, "in Take ~Derived ~Base empty end",
       "std::move transfers ownership to p, so the object is destroyed when p goes out "
       "of scope at the end of Take (derived destructor first, then base). owner is "
       "left empty."},

      {"Smart pointers", Kind::kChoice, "Which marked line fails to compile?",
       R"cpp(void Peek(A* p);
void Take(std::unique_ptr<A> p);

auto owner = std::make_unique<A>();
Peek(owner.get());        // (1)
Take(owner);              // (2)
Take(std::move(owner));   // (3))cpp",
       {"(1)", "(2)", "(3)", "None of them"},
       "B",
       "A unique_ptr cannot be copied - there can only be one owner. get() hands out a "
       "non-owning raw pointer, and std::move explicitly transfers ownership."},
  };
  return questions;
}

std::vector<std::string> Tokens(const std::string& text) {
  std::istringstream in(text);
  std::vector<std::string> tokens;
  std::string token;
  while (in >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

std::string Trim(const std::string& text) {
  auto tokens = Tokens(text);
  std::string result;
  for (const auto& token : tokens) {
    if (!result.empty()) result += " ";
    result += token;
  }
  return result;
}

void PrintIndented(const std::string& code) {
  std::istringstream in(code);
  std::string line;
  while (std::getline(in, line)) {
    std::cout << "    " << line << "\n";
  }
}

enum class Result { kCorrect, kWrong, kSkipped, kQuit };

bool ReadAnswer(std::string& line) {
  std::cout << "> " << std::flush;
  return static_cast<bool>(std::getline(std::cin, line));
}

Result Ask(const Question& q, int number, int total) {
  std::cout << "\n------------------------------------------------------------\n"
            << "Question " << number << "/" << total << "  [" << q.topic << "]\n\n"
            << q.prompt << "\n";
  if (!q.code.empty()) {
    std::cout << "\n";
    PrintIndented(q.code);
  }
  std::cout << "\n";
  if (q.kind == Kind::kChoice) {
    for (std::size_t i = 0; i < q.options.size(); i++) {
      std::cout << "  " << static_cast<char>('A' + i) << ") " << q.options[i] << "\n";
    }
    std::cout << "\nAnswer with a letter (s = skip, q = quit).\n";
  } else {
    std::cout << "Type everything it prints, in order, on ONE line separated by spaces\n"
              << "(s = skip, q = quit).\n";
  }

  std::string line;
  while (true) {
    if (!ReadAnswer(line)) return Result::kQuit;
    std::string answer = Trim(line);
    if (answer == "q" || answer == "Q") return Result::kQuit;
    if (answer == "s" || answer == "S") {
      std::cout << "Skipped. The answer was: " << q.answer << "\n" << q.explanation << "\n";
      return Result::kSkipped;
    }
    if (answer.empty()) continue;

    bool correct;
    if (q.kind == Kind::kChoice) {
      char letter = static_cast<char>(std::toupper(static_cast<unsigned char>(answer[0])));
      if (answer.size() != 1 || letter < 'A' ||
          letter >= static_cast<char>('A' + q.options.size())) {
        std::cout << "Please type one of the option letters.\n";
        continue;
      }
      correct = std::string(1, letter) == q.answer;
    } else {
      correct = Tokens(answer) == Tokens(q.answer);
    }

    if (correct) {
      std::cout << "Correct!\n";
    } else {
      std::cout << "Not quite. The answer is: " << q.answer << "\n";
    }
    std::cout << "Why: " << q.explanation << "\n";
    return correct ? Result::kCorrect : Result::kWrong;
  }
}

// Asks every question in `questions`. Returns the ones answered wrongly or skipped,
// or sets `quit` if the user quit part-way.
std::vector<const Question*> RunQuiz(const std::vector<const Question*>& questions,
                                     bool& quit) {
  std::map<std::string, std::pair<int, int>> by_topic;  // topic -> (correct, asked)
  std::vector<const Question*> missed;
  int correct = 0;
  int asked = 0;
  quit = false;

  for (std::size_t i = 0; i < questions.size(); i++) {
    const Question& q = *questions[i];
    Result result = Ask(q, static_cast<int>(i) + 1, static_cast<int>(questions.size()));
    if (result == Result::kQuit) {
      quit = true;
      break;
    }
    asked++;
    by_topic[q.topic].second++;
    if (result == Result::kCorrect) {
      correct++;
      by_topic[q.topic].first++;
    } else {
      missed.push_back(&q);
    }
  }

  std::cout << "\n============================================================\n"
            << "Score: " << correct << "/" << asked;
  if (asked > 0) std::cout << "  (" << (100 * correct / asked) << "%)";
  std::cout << "\n\nBy topic:\n";
  for (const auto& topic : TopicOrder()) {
    auto it = by_topic.find(topic);
    if (it == by_topic.end()) continue;
    auto [right, total] = it->second;
    std::cout << "  " << topic << std::string(18 - topic.size(), ' ') << right << "/"
              << total << (right == total ? "" : "   <- revise") << "\n";
  }
  std::cout << "============================================================\n";
  return missed;
}

std::vector<const Question*> QuestionsFor(const std::string& topic) {
  std::vector<const Question*> result;
  for (const auto& q : AllQuestions()) {
    if (topic.empty() || q.topic == topic) result.push_back(&q);
  }
  return result;
}

}  // namespace

int main() {
  std::cout << "C++ Crash Course - concept quiz\n"
            << "===============================\n"
            << "As in the slides, print(expr); is shorthand for\n"
            << "    std::cout << expr << std::endl;\n"
            << "and code snippets assume the right #includes.\n";

  while (true) {
    std::cout << "\nMenu:\n"
              << "  1) Full quiz (" << AllQuestions().size() << " questions)\n"
              << "  2) One topic\n"
              << "  3) Quit\n";
    std::string choice;
    if (!ReadAnswer(choice)) return 0;
    choice = Trim(choice);

    std::vector<const Question*> questions;
    if (choice == "1") {
      questions = QuestionsFor("");
    } else if (choice == "2") {
      const auto& topics = TopicOrder();
      for (std::size_t i = 0; i < topics.size(); i++) {
        std::cout << "  " << (i + 1) << ") " << topics[i] << "\n";
      }
      std::string pick;
      if (!ReadAnswer(pick)) return 0;
      int index = 0;
      try {
        index = std::stoi(pick);
      } catch (...) {
      }
      if (index < 1 || index > static_cast<int>(topics.size())) {
        std::cout << "Unknown topic.\n";
        continue;
      }
      questions = QuestionsFor(topics[index - 1]);
    } else if (choice == "3" || choice == "q") {
      return 0;
    } else {
      continue;
    }

    bool quit = false;
    auto missed = RunQuiz(questions, quit);
    while (!quit && !missed.empty()) {
      std::cout << "\nRetry the " << missed.size() << " question(s) you missed? (y/n)\n";
      std::string again;
      if (!ReadAnswer(again)) return 0;
      if (Trim(again) != "y" && Trim(again) != "Y") break;
      missed = RunQuiz(missed, quit);
    }
    if (!quit && missed.empty() && !questions.empty()) {
      std::cout << "\nEverything answered correctly - nice work.\n";
    }
  }
}
