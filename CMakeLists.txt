cmake_minimum_required(VERSION 3.14)
project(dll_test)

set(CMAKE_CXX_STANDARD 17)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)
#add_library(dll_test SHARED library.cpp library.h)
#add_library(dll_test MODULE library.cpp library.h shared_memory.h)
#target_compile_options(dll_test PUBLIC "-fleading-underscore")
#target_link_options(dll_test PUBLIC "-W")

#set_target_properties(dll_test PROPERTIES PREFIX "")
#set_target_properties(dll_test PROPERTIES OUTPUT_NAME "dll-shared-memory")
#add_executable(dll_host host.cpp shared_memory.h)