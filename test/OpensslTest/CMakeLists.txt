#工程名
SET(PROJECT_NAME "OpensslTest")
project(${PROJECT_NAME})
enable_language(CXX)
cmake_minimum_required(VERSION 2.8)
if(UNIX)
	add_compile_options(-std=c++11)
	add_definitions(-D LINUX)
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


if(WIN32)
	#release版本下，产生pdb文件
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif(WIN32)


add_package(src ./src)
add_package(openssl ../../libs/openssl/include)

message(STATUS "MSVC: " ${MSVC})
message(STATUS "MSVC_VERSION: " ${MSVC_VERSION})
message(STATUS "CMAKE_CL_64: " ${CMAKE_CL_64})
if(CMAKE_CL_64)
if(MSVC_VERSION EQUAL 1800)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/openssl/1.1/dynamic/win64_2013)
else(MSVC_VERSION EQUAL 1800)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/openssl/1.1/dynamic/win64_2019)
endif(MSVC_VERSION EQUAL 1800)
ELSE(CMAKE_CL_64)
if(MSVC_VERSION EQUAL 1800)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/openssl/1.1/dynamic/win32_2013)
else(MSVC_VERSION EQUAL 1800)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/openssl/1.1/dynamic/win32_2019)
endif(MSVC_VERSION EQUAL 1800)
endif(CMAKE_CL_64)

#添加工程
add_executable(${PROJECT_NAME} ${all_file})

#链接库
target_link_libraries(${PROJECT_NAME} WS2_32.LIB CRYPT32.LIB libcrypto libssl)
