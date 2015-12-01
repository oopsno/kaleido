cmake_minimum_required(VERSION 3.3)
project(kaleido-lang)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

find_package(flex)
find_package(bison)

include_directories(include gen)

bison_target(gen "gen/k.yy" ${CMAKE_CURRENT_SOURCE_DIR}/gen/parser.cpp)
flex_target(gen "gen/k.ll" ${CMAKE_CURRENT_SOURCE_DIR}/gen/lexer.cpp)

file(GLOB NODE_SRC "src/node/*.cpp")

add_library(lib-node ${NODE_SRC})
add_library(lib-parser src/driver.cpp ${BISON_gen_OUTPUT_SOURCE} ${FLEX_gen_OUTPUTS})
add_library(lib-scope src/scope.cpp)
add_library(lib-context src/context.cpp)

add_subdirectory(test)

