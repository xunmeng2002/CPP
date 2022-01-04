cmake_minimum_required (VERSION 3.8)

project ("GetAddrinfoTest")

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CURRENT_SYSTEM Linux)
	add_definitions("-DLINUX")
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(CURRENT_SYSTEM Windows)
	add_definitions("-DWINDOWS")
ENDIF()

# 将源代码添加到此项目的可执行文件。
add_executable (GetAddrinfoTest "GetAddrinfoTest.cpp")

# TODO: 如有需要，请添加测试并安装目标。
