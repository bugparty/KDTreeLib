cmake_minimum_required(VERSION 3.27)
project(kdTreeLib)
find_package(PCL 1.8 REQUIRED)
#for documentation generation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    # Request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started.")

    # Note the option ALL which allows to build the docs together with the application
    add_custom_target( docs_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else(DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation, please install it with: sudo apt-get install doxygen,macos brew install doxygen")
endif(DOXYGEN_FOUND)
include_directories(include
        thirdparty
        ${PCL_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 17)

add_executable(kdTreeLib src/main.cpp
        include/kdtree_lib/KdTreeLib.cpp
        include/kdtree_lib/KdTreeLib.hpp)
target_link_libraries(kdTreeLib ${PCL_LIBRARIES})