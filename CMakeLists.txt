cmake_minimum_required(VERSION 3.21)
project(rr-lensflares)

set(CMAKE_CXX_STANDARD 17)

set(owl_dir ${PROJECT_SOURCE_DIR}/owl)
add_subdirectory(${owl_dir} EXCLUDE_FROM_ALL)

add_subdirectory(src)