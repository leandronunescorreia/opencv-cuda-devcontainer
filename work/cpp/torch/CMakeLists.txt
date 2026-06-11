cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(check_torch)

find_package(Torch REQUIRED PATHS "/work/work/thirdparty/libtorch" )

add_executable(check check.cpp)
target_link_libraries(check "${TORCH_LIBRARIES}")
set_property(TARGET check PROPERTY CXX_STANDARD 17)
