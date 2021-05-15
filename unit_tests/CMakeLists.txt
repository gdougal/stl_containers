cmake_minimum_required(VERSION 3.17)
project(Google_tests)

set(CMAKE_CXX_STANDARD 98)
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../srcs ../rcs/ft_utils)
set(TEST_FILES
        test.cpp
#        list.cpp
#        vector.cpp
#        stack.cpp
#        queue.cpp
        map.cpp
        )

add_executable(Google_Tests_run ${TEST_FILES})
target_link_libraries(Google_Tests_run gtest gtest_main)

