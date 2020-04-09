cmake_minimum_required(VERSION 2.8)
include(../Common.cmake)
#工程名
SET(PROJECT_NAME "Parser")
project(${PROJECT_NAME})

add_package(Src ./Src)

add_definitions("-D_CRT_SECURE_NO_WARNINGS")

add_executable(${PROJECT_NAME} ${all_file})
