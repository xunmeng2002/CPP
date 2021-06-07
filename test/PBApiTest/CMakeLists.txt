#工程名
SET(PROJECT_NAME "PBApiTest")
project(${PROJECT_NAME})
enable_language(CXX)
cmake_minimum_required(VERSION 2.8)
if(UNIX)
	add_compile_options(-std=c++11)
	add_definitions(-D LINUX)
	add_compile_options(-g)
endif(UNIX)
#宏定义，添加一个包
#name：是一个不带双引号的字符
#dir：是一个不带引号的路径
macro(add_package name dir)
	include_directories(${dir})
	set(hfind ${ARGV1})
	string(APPEND hfind "/*.h")
	set(cfind ${ARGV1})
	string(APPEND cfind "/*.cpp")
	file(GLOB_RECURSE name_header ${hfind})
	file(GLOB_RECURSE name_cpp ${cfind})
	source_group(${ARGV0} FILES ${name_header} ${name_cpp})
	set(all_file ${all_file} ${name_header} ${name_cpp})
endmacro(add_package)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libc.lib")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  /NODEFAULTLIB:nafxcw.lib /NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:msvcrt.lib")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")

add_package(src ./src)
add_package(GenCode ./GenCode)
add_package(StepApiFunc ./StepApiFunc)
add_package(Utility ../../source/Utility)
add_package(MemCache ../../source/MemCache)
add_package(ThreadBase ../../source/ThreadBase)
add_package(Logger ../../source/Logger)
add_package(jsoncpp ../../source/jsoncpp)
add_package(pbapi ../../libs/pbapi/include)
add_package(openssl_c ../../libs/openssl/include)
add_package(base64 ../../source/base64)
add_package(pbsecurity ../../libs/pbsecurity/Client)


add_definitions("-D_CRT_SECURE_NO_WARNINGS")

if(CMAKE_CL_64)
	message(STATUS "CMAKE_CL_64: " ${CMAKE_CL_64})
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/openssl/win64)
	
	#link_directories(${PROJECT_SOURCE_DIR}/../../libs/pbsecurity/Client/vc120_x64_md)
	#link_directories(${PROJECT_SOURCE_DIR}/../../libs/pbsecurity/Client/vc120_x64_mt)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/pbsecurity/Client/vc142_x64_md)
	#link_directories(${PROJECT_SOURCE_DIR}/../../libs/pbsecurity/Client/vc142_x64_mt)
	
	
ELSE(CMAKE_CL_64)
	message(STATUS "CMAKE_CL_64: " ${CMAKE_CL_64})
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/openssl/win32)

	#link_directories(${PROJECT_SOURCE_DIR}/../../libs/pbsecurity/Client/A1_win32)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/pbsecurity/Client/vc120_md)
	#link_directories(${PROJECT_SOURCE_DIR}/../../libs/pbsecurity/Client/vc120_mt)
	#link_directories(${PROJECT_SOURCE_DIR}/../../libs/pbsecurity/Client/vc142_md)
	#link_directories(${PROJECT_SOURCE_DIR}/../../libs/pbsecurity/Client/vc142_mt)
endif()

add_executable(${PROJECT_NAME} ${all_file})
target_link_libraries(${PROJECT_NAME} WS2_32.LIB CRYPT32.LIB libcrypto libssl SecurityLib_A6)
#target_link_libraries(${PROJECT_NAME} WS2_32.LIB CRYPT32.LIB libcrypto libssl SecurityLib_A1)
