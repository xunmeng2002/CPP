cmake_minimum_required(VERSION 2.8)
include(../Common.cmake)
project(TcpIOCPClient)

add_package(src ./src)
add_package(ThreadBase ../../source/ThreadBase)
add_package(Utility ../../source/Utility)
add_package(CacheList ../../source/CacheList)
add_package(MemCache ../../source/MemCache)
add_package(Event ../../source/Event)
add_package(Logger ../../source/Logger)
add_package(SocketInit ../../source/SocketInit)
add_package(SocketMemCache ../../source/SocketMemCache)
add_package(TcpBase ../../source/Tcp/TcpBase)
add_package(TcpIOCP ../../source/Tcp/TcpIOCP)


add_definitions("-D_CRT_SECURE_NO_WARNINGS")
add_executable(TcpIOCPClient ${all_file})
