cmake_minimum_required(VERSION 3.3)
project(kaleido-lang)

set(LLVM_HOME "/usr/local/opt/llvm")
set(LLVM_BIN "${LLVM_HOME}/bin")
set(LLVM_LIB "${LLVM_HOME}/lib")
set(LLVM_INCLUDE "${LLVM_HOME}/include")
find_library(LLVM
        NAMES LLVMCore LLVMSupport LLVM
        PATHS ${LLVM_LIB} NO_DEFAULT_PATH)


set(CMAKE_CXX_STANDARD 11)

execute_process(
        COMMAND llvm-config --cxxflags --ldflags --system-libs --libs core
        OUTPUT_VARIABLE LLVM_CONFIG_MULINE)

string(REGEX REPLACE "\n" " " LLVM_CONFIG ${LLVM_CONFIG_MULINE})

message(STATUS "[llvm-config]" ${LLVM_CONFIG})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CONFIG} -Wno-unused-parameter")

find_package(flex)
find_package(bison)

include_directories(include gen ${LLVM_INCLUDE})

bison_target(gen "gen/k.yy" ${CMAKE_CURRENT_SOURCE_DIR}/gen/parser.cpp)
flex_target(gen "gen/k.ll" ${CMAKE_CURRENT_SOURCE_DIR}/gen/lexer.cpp)

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

add_subdirectory(test)

