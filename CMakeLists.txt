cmake_minimum_required(VERSION 3.24)
project(CppCrashCourseTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build the exercise tests against solutions/ instead of part2_exercises/.
# In CLion: Settings > Build, Execution, Deployment > CMake > CMake options: -DUSE_SOLUTIONS=ON
option(USE_SOLUTIONS "Build the exercise tests against the model solutions" OFF)

# Link the MinGW runtime statically so the test executables run outside CLion too.
if(MINGW)
  add_link_options(-static)
endif()

# ---------------------------------------------------------------------------
# GoogleTest (downloaded once, on the first CMake load)
# ---------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# ---------------------------------------------------------------------------
# Part 1: interactive concept quiz
# ---------------------------------------------------------------------------
add_executable(1_quiz part1_quiz/quiz.cpp)

# ---------------------------------------------------------------------------
# Part 2: coding exercises - one test executable per exercise, so an
# unfinished exercise never stops the others from building.
# ---------------------------------------------------------------------------
function(add_exercise name)
  if(USE_SOLUTIONS)
    set(impl_dir ${CMAKE_CURRENT_SOURCE_DIR}/solutions/${name})
  else()
    set(impl_dir ${CMAKE_CURRENT_SOURCE_DIR}/part2_exercises/${name})
  endif()
  file(GLOB impl_files CONFIGURE_DEPENDS ${impl_dir}/*.h ${impl_dir}/*.cc)

  add_executable(${name}_test tests/test_${name}.cpp ${impl_files})
  target_include_directories(${name}_test PRIVATE ${impl_dir})
  target_link_libraries(${name}_test PRIVATE GTest::gtest_main)
  # -Wall includes warnings that catch crash-course mistakes, e.g. hidden
  # virtual methods and deleting through a base without a virtual destructor.
  if(NOT MSVC)
    target_compile_options(${name}_test PRIVATE -Wall)
  endif()
  gtest_discover_tests(${name}_test DISCOVERY_MODE PRE_TEST)
endfunction()

add_exercise(ex01_strings_io)
add_exercise(ex02_classes)
add_exercise(ex03_inheritance)
add_exercise(ex04_fix_the_bugs)
add_exercise(ex05_templates)
add_exercise(ex06_references_params)
add_exercise(ex07_vectors_algorithms)
add_exercise(ex08_lambdas)
add_exercise(ex09_destructors_raii)
add_exercise(ex10_unique_ptr)
add_exercise(ex11_capstone)
