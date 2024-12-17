#CMAKE VERSION
cmake_minimum_required(VERSION 3.12)

#Project name
project(symbolic-ai)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")

add_subdirectory(src)