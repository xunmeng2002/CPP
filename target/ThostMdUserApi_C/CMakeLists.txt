#工程名
project(ThostMdUserApi_C)
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

#定义变量BIT 32位还是64位
if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
	SET(BIT 64)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
	SET(BIT 32)
endif ( CMAKE_SIZEOF_VOID_P EQUAL 8 )

if(CMAKE_BUILD_TYPE)
if(${CMAKE_BUILD_TYPE} STREQUAL "debug")
	add_definitions(-D _DEBUG)
endif(${CMAKE_BUILD_TYPE} STREQUAL "debug")
endif(CMAKE_BUILD_TYPE)

#windows上使用静态编译
if(WIN32)
	set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
	foreach(CompilerFlag ${CompilerFlags})
		string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
	endforeach()
	
	#release版本下，产生pdb文件
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
	
	#设置子系统最低版本为5.1
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE,5.01")
endif(WIN32)

add_package(src ./src)
add_package(API ../../source/API/ThostMdUserApi/include)

add_definitions("-DPB_MD_API_IS_LIB")
add_definitions("-DISLIB")


#添加库目录
if(WIN32)
	if(${BIT} EQUAL 32)
		link_directories(${PROJECT_SOURCE_DIR}/../../source/API/ThostMdUserApi/win32)
	else(${BIT} EQUAL 32)
		link_directories(${PROJECT_SOURCE_DIR}/../../source/API/ThostMdUserApi/win64)
	endif(${BIT} EQUAL 32)
elseif(UNIX)
	link_directories(${PROJECT_SOURCE_DIR}/../../source/API/ThostMdUserApi/linux)
endif()

#添加工程
add_library(ThostMdUserApi_C SHARED ${all_file})

#链接库
if(WIN32)
	target_link_libraries(ThostMdUserApi_C ThostMdUserApi)
elseif(UNIX)
	target_link_libraries(ThostMdUserApi_C ThostMdUserApi)
endif()