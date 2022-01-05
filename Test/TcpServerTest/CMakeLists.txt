cmake_minimum_required (VERSION 3.8)
include(../../Common.cmake)
SET(PROJECT_NAME "TcpServerTest")
project(${PROJECT_NAME})


add_package(src ./src)
add_package(SocketInit ../../source/SocketInit)


# 将源代码添加到此项目的可执行文件。
add_executable(${PROJECT_NAME} ${all_file})

# TODO: 如有需要，请添加测试并安装目标。
