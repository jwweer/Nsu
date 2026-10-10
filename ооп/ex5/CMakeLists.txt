cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(test_proj VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(my_lib)

add_executable(exec_trg s03.cpp)
target_link_libraries(exec_trg PUBLIC mylib)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()