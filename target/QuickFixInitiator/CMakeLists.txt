cmake_minimum_required(VERSION 2.8)
include(../../Common.cmake)
SET(PROJECT_NAME "QuickFixInitiator")
SET(APIVersion "1.15.1")
project(${PROJECT_NAME})


add_package(src ./src)
add_package(Utility ../../source/Utility)
add_package(MemCache ../../source/MemCache)
add_package(ThreadBase ../../source/ThreadBase)
add_package(Logger ../../source/Logger)
add_package(jsoncpp ../../source/jsoncpp)

add_package(quickfix ../../libs/quickfix/${APIVersion}/include)
add_package(cryptopp ../../libs/cryptopp/8.5.0/include)

add_definitions("-D_CRT_SECURE_NO_WARNINGS")

message(STATUS "CMAKE_CL_64: " ${CMAKE_CL_64})
if(CMAKE_CL_64)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/quickfix/${APIVersion}/win64)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/cryptopp/8.5.0/win64)
ELSE(CMAKE_CL_64)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/quickfix/${APIVersion}/win32)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/cryptopp/8.5.0/win32)
endif(CMAKE_CL_64)

add_executable(${PROJECT_NAME} ${all_file})

target_link_libraries(${PROJECT_NAME} ws2_32.lib quickfixd.lib cryptlib.lib)