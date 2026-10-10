# C++ Crash Course: knowledge test

A self-test for the *C++ Crash Course* (60007, Theory and Practice of Concurrent
Programming). It has two parts:

1. **Concept quiz** (`1_quiz`): 32 interactive questions. Most ask you to predict the
   output or say which line fails to compile. You get an explanation after every
   answer and a score per topic at the end.
2. **Coding exercises** (`ex01` to `ex11`): you implement code against GoogleTest tests,
   ending with a capstone that combines every topic.

## Getting your own copy

Click **Use this template > Create a new repository** at the top of this page to get
your own copy. Make it **private** if you don't want your answers to be public. Then
clone it. If you don't want a GitHub repo, `git clone` this one or download the ZIP.

Keep your answers in your own copy. Please don't open pull requests here with your
solutions.

## Opening in CLion

1. **File > Open...** and select the folder you cloned. Trust the project.
2. Use the default toolchain (CLion's bundled MinGW). The first CMake load downloads
   GoogleTest (v1.15.2), so you need internet the first time only.
3. Your Run/Debug configuration dropdown now has:
   * `1_quiz`: the concept quiz
   * `ex01_strings_io_test` ... `ex11_capstone_test`: one per exercise
   * `All CTest`: every exercise test at once. If CLion didn't create it, add it via
     **Run > Edit Configurations > + > CTest Application**.

Each test file also shows green "run" arrows in the gutter next to each `TEST`.

## Part 1: the quiz

Run `1_quiz` and type answers into the **Run** console.

* Multiple choice: type the letter.
* "What does this print?": type everything it prints, in order, on one line, separated
  by spaces. Spacing doesn't matter, but spelling and punctuation do.
* `s` skips a question (it shows the answer), and `q` returns to the menu.
* After a round you can retry just the questions you missed.

As in the slides, `print(expr);` means `std::cout << expr << std::endl;`.

Don't read `part1_quiz/quiz.cpp` before taking the quiz, because the answers are in it.

## Part 2: the exercises

Edit only the files in `part2_exercises/`. The tests are in `tests/`, so don't edit
those. Every exercise compiles out of the box and its tests fail until you implement it.
One unfinished exercise never stops the others from building.

| #  | Folder                    | Tests your grasp of |
|----|---------------------------|---------------------|
| 01 | `ex01_strings_io`         | `std::string`, `append`, `std::to_string`, `std::ostream`, cout vs cerr |
| 02 | `ex02_classes`            | `.h`/`.cc` split, `A::Method`, initializer lists, `const` methods, `explicit` |
| 03 | `ex03_inheritance`        | `virtual`/`override`, hiding vs overriding, abstract classes, virtual destructors, calling base constructors and methods |
| 04 | `ex04_fix_the_bugs`       | Six classic gotchas, each fixable with a one-keyword or one-character change |
| 05 | `ex05_templates`          | Class and function templates, implicit requirements on `T`, `this->` in templated subclasses |
| 06 | `ex06_references_params`  | The parameter-passing cheat sheet (value / `const&` / `&` / `const*` / `*`). Signatures are tested too |
| 07 | `ex07_vectors_algorithms` | `std::vector`, `std::find`, iterators, `erase`, `auto`, range-for by reference. Bonus: `std::map` |
| 08 | `ex08_lambdas`            | `std::function`, passing and returning lambdas, capture by value vs by reference |
| 09 | `ex09_destructors_raii`   | Object lifetime, destruction order, composite objects, plus a scoping puzzle |
| 10 | `ex10_unique_ptr`         | Linked list built from `std::unique_ptr` (the live-coding demo), `make_unique`, `.get()`, `std::move` |
| 11 | `ex11_capstone`           | A task scheduler that uses all of the above |

Each exercise header starts with a short brief and `TODO`s. Some declarations in the
headers are deliberately incomplete or wrong, and the failing tests and their messages
tell you what's missing. Exercises are roughly in course order, but they're independent,
so you can do them in any order.

Your score is the `All CTest` summary, e.g. `87% tests passed, 16 tests failed out of
123`. A test that fails with `C++ exception with description "TODO: ..."` just means
you haven't implemented that part yet.

The project compiles with `-Wall`. Read the compiler warnings, because several of them
point straight at crash-course mistakes.

## Model solutions (spoilers!)

`solutions/` contains a complete, commented solution for every exercise. To compare
your results with them without touching your own code, add a second CMake profile:

**Settings > Build, Execution, Deployment > CMake > +**, name it `Solutions`, and set
**CMake options** to `-DUSE_SOLUTIONS=ON`.

Pick the profile in the run configuration dropdown, and every `exNN_test` then builds
against `solutions/` instead of `part2_exercises/`. Switch back to `Debug` to test
your own code.
