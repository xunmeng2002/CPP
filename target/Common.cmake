enable_language(CXX)
cmake_minimum_required(VERSION 2.8)

#宏定义，添加一个包
#name：是一个不带双引号的字符
#dir：是一个不带引号的路径
macro(add_package name dir)
	include_directories(${dir})
	set(hfind ${ARGV1})
	string(APPEND hfind "/*.h")
	set(hppfind ${ARGV1})
	string(APPEND hppfind "/*.hpp")
	set(cppfind ${ARGV1})
	string(APPEND cppfind "/*.cpp")
	set(cfind ${ARGV1})
	string(APPEND cfind "/*.c")
	file(GLOB_RECURSE name_header ${hfind})
	file(GLOB_RECURSE name_hpp ${hppfind})
	file(GLOB_RECURSE name_cpp ${cppfind})
	file(GLOB_RECURSE name_c ${cfind})
	source_group(${ARGV0} FILES  ${name_header} ${name_hpp} ${name_cpp} ${name_c})
	set(all_file ${all_file}  ${name_header}  ${name_hpp} ${name_cpp} ${name_c})
endmacro(add_package)

#宏定义，添加一个包
#name：是一个不带双引号的字符
#dir：是一个不带引号的路径
macro(add_package_all name dir)
	include_directories(${dir})
	set(hfind ${ARGV1})
	string(APPEND hfind "/*.*")
	file(GLOB_RECURSE name_header ${hfind})
	source_group(${ARGV0} FILES  ${name_header} )
	set(all_file ${all_file}  ${name_header} )
endmacro(add_package_all)

if(UNIX)
	add_compile_options(-std=c++11)
	add_definitions(-D LINUX)
	add_compile_options(-g)
endif(UNIX)

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
		string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
	endforeach()
	
	#release版本下，产生pdb文件
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
	set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
	
	#设置SAFESEH为NO
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
	set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")
endif(WIN32)