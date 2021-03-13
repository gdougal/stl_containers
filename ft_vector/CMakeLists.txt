cmake_minimum_required(VERSION 3.17)
project(ft_vector)

set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_FLAGS "-Wclass-memaccess")

add_executable(ft_vector
        main.cpp
        vector.cpp
        vector.hpp
        )