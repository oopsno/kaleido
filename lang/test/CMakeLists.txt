cmake_minimum_required(VERSION 3.3)
project(kaleido-lang-test)

file(GLOB SRC "../src/*.cpp")

add_executable(test-node   node.cpp ../src/node.cpp)
add_executable(test-parser parser.cpp ${SRC} ../gen/lexer.cpp ../gen/parser.cpp)

