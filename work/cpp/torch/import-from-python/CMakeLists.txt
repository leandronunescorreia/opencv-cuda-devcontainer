cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(inference)

find_package(Torch REQUIRED PATHS "/work/work/thirdparty/libtorch" )

add_executable(inference inference.cpp)
target_link_libraries(inference "${TORCH_LIBRARIES}")
set_property(TARGET inference PROPERTY CXX_STANDARD 17)
