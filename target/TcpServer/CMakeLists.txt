cmake_minimum_required(VERSION 2.8)
include(../../Common.cmake)
SET(PROJECT_NAME "TcpServer")
project(${PROJECT_NAME})


add_package(src ./src)
add_package(TcpServer ./TcpServer)
add_package(TcpServerSelect ./TcpServerSelect)
add_package(Udp ../../source/Udp)
add_package(Utility ../../source/Utility)
add_package(MemCache ../../source/MemCache)
add_package(MyEvent ../../source/MyEvent)
add_package(ThreadBase ../../source/ThreadBase)
add_package(Logger ../../source/Logger)
add_package(SocketInit ../../source/SocketInit)
add_package(CacheList ../../source/CacheList)
add_package(Zlib ../../Libs/Zlib)


add_definitions("-D_CRT_SECURE_NO_WARNINGS")

add_executable(${PROJECT_NAME} ${all_file})
