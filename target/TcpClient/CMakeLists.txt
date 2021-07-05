cmake_minimum_required(VERSION 2.8)
include(../../Common.cmake)
SET(PROJECT_NAME "TcpClient")
project(${PROJECT_NAME})


add_package(src ./src)
add_package(Utility ../../source/Utility)
add_package(MemCache ../../source/MemCache)
add_package(ThreadBase ../../source/ThreadBase)
add_package(Logger ../../source/Logger)
add_package(SocketInit ../../source/SocketInit)


add_definitions("-D_CRT_SECURE_NO_WARNINGS")

add_executable(${PROJECT_NAME} ${all_file})
