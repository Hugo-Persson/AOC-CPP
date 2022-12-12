cmake_minimum_required(VERSION 3.20)
project(AoC)
set(CMAKE_C_COMPILER "gcc-4.2")
set(CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_STANDARD 20)
enable_testing()

# Glob cmake files for days in cmake/ directory and include them
file(GLOB cmake_days ${CMAKE_CURRENT_SOURCE_DIR}/cmake/[^_]*.cmake)

foreach(day ${cmake_days})
  include(${day})
endforeach()
