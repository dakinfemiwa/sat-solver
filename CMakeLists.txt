#CMAKE VERSION
cmake_minimum_required(VERSION 3.12)

if (POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

#Project name
project(symbolic-ai)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")

add_subdirectory(src)

add_subdirectory(googletest)

add_subdirectory(test)

target_link_libraries(formulatests gtest gtest_main pthread)