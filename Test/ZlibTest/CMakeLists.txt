cmake_minimum_required(VERSION 2.8)
include(../../Common.cmake)
SET(PROJECT_NAME "ZlibTest")
project(${PROJECT_NAME})


add_package(src ./src)
add_package(Zlib ../../Libs/Zlib)


add_definitions("-D_CRT_SECURE_NO_WARNINGS")

add_executable(${PROJECT_NAME} ${all_file})
