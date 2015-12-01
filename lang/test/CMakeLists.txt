cmake_minimum_required(VERSION 3.3)
project(kaleido-lang-test)

add_executable(test-node node.cpp)
target_link_libraries(test-node lib-node)

add_executable(test-parser parser.cpp)
target_link_libraries(test-parser lib-node lib-parser lib-scope)


