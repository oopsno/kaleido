cmake_minimum_required(VERSION 3.3)
project(kaleido-lang-test)

file(GLOB SRC "../src/*.cpp")

add_executable(test-node node.cpp)
add_dependencies(test-node lib-node)
target_link_libraries(test-node lib-node)

add_executable(test-parser parser.cpp ${SRC} ../gen/lexer.cpp ../gen/parser.cpp)

