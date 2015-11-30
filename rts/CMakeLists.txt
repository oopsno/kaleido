cmake_minimum_required(VERSION 3.3)
project(kaleido-rts)

set(CMAKE_C_STANDARD 11)

include_directories(${CMAKE_INCLUDE_PATH} include)

add_executable(test_color src/draw.c test/test_rgbd.c)