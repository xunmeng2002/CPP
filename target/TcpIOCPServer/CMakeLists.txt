cmake_minimum_required(VERSION 2.8)
include(../Common.cmake)
project(TcpIOCPServer)

add_package(src ./src)
add_package(ThreadBase ../../source/ThreadBase)
add_package(Utility ../../source/Utility)
add_package(CacheList ../../source/CacheList)
add_package(MemCache ../../source/MemCache)
add_package(Event ../../source/Event)
add_package(SocketInit ../../source/SocketInit)
add_package(SocketMemCache ../../source/SocketMemCache)
add_package(IOCompletePort ../../source/Tcp/IOCompletePort)
add_package(WorkThreadBase ../../source/WorkThreadBase)
add_package(Logger ../../source/Logger)


add_definitions("-D_CRT_SECURE_NO_WARNINGS")
add_executable(TcpIOCPServer ${all_file})
