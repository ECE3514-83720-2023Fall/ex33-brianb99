cmake_minimum_required(VERSION 3.9...3.19)
project(Meeting33 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# build tests
add_executable(unit_tests catch.hpp unit_tests.cpp
abstract_dictionary.hpp
hash_dictionary.hpp hash_dictionary.tpp
test_dictionary.cpp
)

add_executable(instructor_tests catch.hpp unit_tests.cpp
abstract_dictionary.hpp
hash_dictionary.hpp hash_dictionary.tpp
.github/instructor_tests.cpp
)
