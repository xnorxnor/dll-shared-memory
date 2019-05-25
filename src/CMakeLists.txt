add_library(dll_test MODULE library.cpp library.h shared_memory.h)
#target_compile_options(dll_test PUBLIC "-fleading-underscore")
#target_link_options(dll_test PUBLIC "-W")

set_target_properties(dll_test PROPERTIES PREFIX "")
set_target_properties(dll_test PROPERTIES OUTPUT_NAME "dll-shared-memory")
add_executable(dll_host host.cpp shared_memory.h)