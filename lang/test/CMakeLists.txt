cmake_minimum_required(VERSION 3.3)
project(kaleido-lang-test)

add_executable(test-parser parser.cpp)
target_link_libraries(test-parser lib-ast lib-parser lib-err lib-codegen lib-dump)

add_executable(test-dump-common dump_common.cpp)
target_link_libraries(test-dump-common lib-dump)


add_executable(test-ast ast.cpp)
target_link_libraries(test-ast lib-dump lib-ast lib-context lib-codegen )

set_target_properties(test-ast test-parser
        PROPERTIES COMPILE_FLAGS ${CXX_FLAGS_WITH_LLVM}
                   LINK_FLAGS    ${LLVM_LINK_FLAGS})
