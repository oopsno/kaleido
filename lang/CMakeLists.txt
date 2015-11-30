cmake_minimum_required(VERSION 3.3)
project(kaleido-lang)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

find_package(flex)
find_package(bison)

include_directories(include)

add_subdirectory(lib)
