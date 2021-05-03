cmake_minimum_required(VERSION 3.19)
project(Google_tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(TEST_FILES
        test.cpp
        list.cpp
        vector.cpp
#        map.cpp
        stack.cpp
        queue.cpp
        )

add_executable(Google_Tests_run ${TEST_FILES})
target_link_libraries(Google_Tests_run gtest gtest_main testlib)

add_subdirectory(lib/googletest)
