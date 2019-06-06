cmake_minimum_required(VERSION 3.10)
project(unix)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp)
add_executable(more03 more03.cpp)

add_executable(who01 who01.c)
add_executable(who02 who02.c )
add_executable(who03 who03.c)


add_executable(cp01 cp01.c)

add_executable(logout01 logout01.c)


add_executable(ls01 ls01.c)

add_executable(ls02 ls02.c)

add_executable(fileinfo fileinfo.c)

