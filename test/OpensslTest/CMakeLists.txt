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

if(CMAKE_BUILD_TYPE)
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_definitions(-D _DEBUG)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
endif(CMAKE_BUILD_TYPE)

if(WIN32)
	#windows上使用静态编译
	set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
	foreach(CompilerFlag ${CompilerFlags})
		string(REPLACE "/MT" "/MD" ${CompilerFlag} "${${CompilerFlag}}")
	endforeach()
	
	#release版本下，产生pdb文件
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
	
	#设置子系统最低版本为5.1
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE,5.01")
endif(WIN32)


add_package(src ./src)
add_package(openssl_c ../../libs/openssl/include)

#添加库目录
if(WIN32)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/openssl/win64_static)
elseif(UNIX)
	link_directories(${PROJECT_SOURCE_DIR}/../../libs/openssl/linux_static)
endif()

#添加工程
add_executable(${PROJECT_NAME} ${all_file})

#链接库
if(WIN32)
	target_link_libraries(${PROJECT_NAME} WS2_32.LIB CRYPT32.LIB libcrypto libssl)
elseif(UNIX)
	target_link_libraries(${PROJECT_NAME} crypto ssl)
endif()