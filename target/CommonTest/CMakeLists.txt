cmake_minimum_required(VERSION 3.0)
SET(PROJECT_NAME "CommonTest")
project(${PROJECT_NAME})

include(../Common.cmake)
add_subdirectory(./CacheListTest)
