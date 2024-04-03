cmake_minimum_required(VERSION 3.27)
project(kdTreeLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(PCL 1.8 REQUIRED)
#setup gtest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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

set(THIRD_PARTY_SOURCES
        thirdparty/ikd-Tree/ikd-Tree/ikd_Tree.cpp
        thirdparty/ikd-Tree/ikd-Tree/ikd_Tree.h
)
add_executable(kdTreeLib src/main.cpp
        include/kdtree_lib/KdTreeLib.cpp
)
target_link_libraries(kdTreeLib ${PCL_LIBRARIES})

enable_testing()

add_executable(
        hello_test
        tests/HelloTest.cpp
        tests/IkdTreeTest.cpp
        tests/RandomPointGenTest.cpp
        ${THIRD_PARTY_SOURCES}
)
target_link_libraries(
        hello_test
        GTest::gtest_main
        ${PCL_LIBRARIES}
)

include(GoogleTest)
gtest_discover_tests(hello_test)