cmake_minimum_required(VERSION 3.26)
project(system_structure)

set(CMAKE_CXX_STANDARD 17)

add_executable(system_structure main.cpp)

target_include_directories(system_structure PUBLIC include)

add_subdirectory(src)