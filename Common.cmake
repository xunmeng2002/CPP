enable_language(CXX)
cmake_minimum_required(VERSION 2.8)
if(UNIX)
	add_compile_options(-std=c++11)
	add_definitions(-D LINUX)
	add_compile_options(-g)
endif(UNIX)

macro(add_file name dir filename)
	include_directories(${dir})
	file(GLOB_RECURSE fullname ${dir}/${filename})
	source_group(${name} FILES ${fullname})
	set(all_file ${all_file} ${fullname})
endmacro(add_file)

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

macro(add_res_package name dir)
	set(resfind ${ARGV1})
	string(APPEND resfind "/*")
	file(GLOB_RECURSE res ${resfind})
	source_group(${ARGV0} FILES ${res})
	set(all_file ${all_file} ${res})
endmacro(add_res_package)