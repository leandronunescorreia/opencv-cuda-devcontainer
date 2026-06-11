cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(simple_blob)

find_package(Torch REQUIRED PATHS "/work/work/thirdparty/libtorch" )
find_package(OpenCV REQUIRED)

add_executable(simple_blob simple_blob.cpp)
target_link_libraries(simple_blob "${TORCH_LIBRARIES}" ${OpenCV_LIBS})
set_property(TARGET simple_blob PROPERTY CXX_STANDARD 17)
