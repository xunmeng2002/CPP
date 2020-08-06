cmake_minimum_required(VERSION 2.8)
include(../../Common.cmake)
#工程名
SET(PROJECT_NAME "CacheListTest")
project(${PROJECT_NAME})

add_package(${PROJECT_NAME} ./src)
add_package(Cases ./Cases)
add_package(UnitTestFrame ../../../source/UnitTestFrame)

add_package(CacheList ../../../source/CacheList)


add_definitions("-D_WINSOCK_DEPRECATED_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS")

#添加工程
add_executable(${PROJECT_NAME} ${all_file})



