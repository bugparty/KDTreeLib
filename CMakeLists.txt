cmake_minimum_required(VERSION 3.27)
project(kdTreeLib)
find_package(PCL 1.8 REQUIRED)

include_directories(include
        thirdparty
        ${PCL_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 17)

add_executable(kdTreeLib main.cpp
        include/kdtree_lib/KdTreeLib.cpp
        include/kdtree_lib/KdTreeLib.hpp)
target_link_libraries(kdTreeLib ${PCL_LIBRARIES})