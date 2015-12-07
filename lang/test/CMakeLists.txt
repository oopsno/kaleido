cmake_minimum_required(VERSION 3.3)
project(kaleido-lang-test)

add_executable(test-node node.cpp)
target_link_libraries(test-node lib-node)

add_executable(test-parser parser.cpp)
target_link_libraries(test-parser lib-node lib-parser lib-scope lib-err)

add_executable(test-dump-common dump_common.cpp)
target_link_libraries(test-dump-common lib-dump-common)


add_executable(test-ast ast.cpp)
target_link_libraries(test-ast lib-dump lib-ast lib-context lib-codegen)
