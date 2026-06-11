cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(torch_simple_linear)

find_package(Torch REQUIRED PATHS "/work/work/thirdparty/libtorch" )

add_executable(simple_linear simple_linear.cpp)
target_link_libraries(simple_linear "${TORCH_LIBRARIES}")
set_property(TARGET simple_linear PROPERTY CXX_STANDARD 17)
