﻿cmake_minimum_required (VERSION 3.8)
SET(PROJECT_NAME "GetAddrinfoTest")
project (${PROJECT_NAME})

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
	message("CMAKE_SYSTEM_NAME Linux:" ${CMAKE_SYSTEM_NAME})
	add_definitions("-DLINUX")
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	message("CMAKE_SYSTEM_NAME Windows:" ${CMAKE_SYSTEM_NAME})
	add_definitions("-DWINDOWS")
ENDIF()

message("CMAKE_SYSTEM_NAME:" ${CMAKE_SYSTEM_NAME})
add_executable(${PROJECT_NAME} "GetAddrinfoTest.cpp")

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
target_link_libraries(${PROJECT_NAME} pthread)
ENDIF()