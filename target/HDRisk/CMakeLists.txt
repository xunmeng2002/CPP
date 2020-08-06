cmake_minimum_required(VERSION 2.8)
include(../Common.cmake)
#工程名
SET(PROJECT_NAME "HDRisk")
project(${PROJECT_NAME})

add_package_all(${PROJECT_NAME} ./Src)
add_package_all(Res ./Res)

add_package_all(DataStruct ../../source/DataStruct)
add_package_all(CacheList ../../source/CacheList)
add_package_all(Socket ../../source/Socket)
add_package_all(ThreadBase ../../source/ThreadBase)
add_package_all(Tcp ../../source/Tcp)
add_package_all(Step ../../source/Step)



#每个工程都需要的宏
add_definitions("-DWINDOWS -DWINDOWSCODE")
add_definitions("-D_CRT_SECURE_NO_WARNINGS -DNO_WARN_MBCS_MFC_DEPRECATION")
add_definitions("-D_WIN32_WINNT=0x0501")
#工程独有的宏
add_definitions("-D_WINSOCK_DEPRECATED_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS")


#set(CMAKE_MFC_FLAG 1)#设置CMAKE_MFC_FLAG为2,0表示使用标准的MFC，1表示静态MFC,2表示共享
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

#添加工程
add_executable(${PROJECT_NAME} ${all_file})
