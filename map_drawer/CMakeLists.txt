cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 11)
project(map_drawer)
set(EXECUTABLE_NAME "map_drawer")
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Frameworks)
add_executable(${EXECUTABLE_NAME}
        main.cpp
        )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${EXECUTABLE_NAME}
       ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-audio.dylib
       ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-graphics.dylib
       ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-network.dylib
       ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-system.dylib
       ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-window.dylib
       )
