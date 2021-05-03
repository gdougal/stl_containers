cmake_minimum_required(VERSION 3.19)
project(containers)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(unit_tests)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} srcs srcs/ft_utils)
set(SRCS ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/)

set(TEST_FILES
        ${SRCS}test.cpp
        ${SRCS}list.cpp
        ${SRCS}vector.cpp
#        ${SRCS}map.cpp
        ${SRCS}stack.cpp
        ${SRCS}queue.cpp
        )

add_executable(containers ${TEST_FILES})
target_link_libraries(Google_Tests_run gtest gtest_main testlib srcs srcs/ft_utils)
