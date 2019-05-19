cmake_minimum_required(VERSION 3.14)
project(dll_test)

set(CMAKE_CXX_STANDARD 17)

#add_library(dll_test SHARED library.cpp library.h)
add_library(dll_test MODULE library.cpp library.h shared_memory.h)

set_target_properties(dll_test PROPERTIES PREFIX "")
set_target_properties(dll_test PROPERTIES OUTPUT_NAME "dll_test")

add_executable(dll_host host.cpp shared_memory.h)