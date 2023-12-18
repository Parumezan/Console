################# CONFIG ##################

#init Cmake
cmake_minimum_required(VERSION 3.25)
project(Console LANGUAGES CXX VERSION 0.1)

## Set project properties
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

################## BUILD ##################

## Set library name
set(LIB Console)

## Set root path
set(LIB_ROOT src/)

## Include directories
include_directories(
    ${LIB_ROOT}/
)

## List source files
set(LIB_SRC
    ${LIB_ROOT}/Console.cpp
)

## Create library
add_library(${LIB} SHARED ${LIB_SRC})

## Set output directory
set_target_properties(${LIB} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set_target_properties(${LIB} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

## Install library
install(TARGETS ${LIB})