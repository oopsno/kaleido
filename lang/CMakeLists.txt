cmake_minimum_required(VERSION 3.3)
project(kaleido-lang)

set(CMAKE_CXX_STANDARD 11)

# Configuartion made by `llvm-config` using
execute_process(
        COMMAND llvm-config --includedir
        OUTPUT_VARIABLE LLVM_INCLUDE_DIR)
execute_process(
        COMMAND llvm-config --cxxflags
        OUTPUT_VARIABLE LLVM_CXX_FLAGS)
execute_process(
        COMMAND llvm-config --ldflags --system-libs --libs core
        OUTPUT_VARIABLE LLVM_LINK_FLAGS_MULINE)

string(REGEX REPLACE "\n" " " LLVM_LINK_FLAGS ${LLVM_LINK_FLAGS_MULINE})

set(CXX_FLAGS_WITH_LLVM "${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS}")

find_package(flex)
find_package(bison)

include_directories(include gen ${LLVM_INCLUDE_DIR})

bison_target(gen "gen/kaleido.yy" ${CMAKE_CURRENT_SOURCE_DIR}/gen/parser.cpp)
flex_target(gen "gen/kaleido.ll" ${CMAKE_CURRENT_SOURCE_DIR}/gen/lexer.cpp)

file(GLOB NODE_SRC "src/node/*.cpp")
file(GLOB CODEGEN_SRC "src/codegen/*.cpp")
file(GLOB AST_SRC "src/ast/*.cpp")
file(GLOB DUMP_SRC "src/dump/*.cpp")

add_library(lib-err src/error.cpp)
add_library(lib-node ${NODE_SRC})
add_library(lib-ast ${AST_SRC})
add_library(lib-parser src/driver.cpp ${BISON_gen_OUTPUT_SOURCE} ${FLEX_gen_OUTPUTS})
add_library(lib-codegen ${CODEGEN_SRC})
add_library(lib-scope src/scope.cpp)
add_library(lib-context src/context.cpp)
add_library(lib-dump ${DUMP_SRC})
set_target_properties(lib-ast lib-parser lib-context lib-dump lib-codegen
        PROPERTIES COMPILE_FLAGS ${CXX_FLAGS_WITH_LLVM})


add_subdirectory(test)

