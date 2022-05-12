cmake_minimum_required(VERSION 3.21)
project(owl_test)

set(CMAKE_CXX_STANDARD 17)

set(owl_dir ${PROJECT_SOURCE_DIR}/owl)
add_subdirectory(${owl_dir} EXCLUDE_FROM_ALL)



embed_ptx(
        OUTPUT_TARGET
        owl_test-ptx
        PTX_LINK_LIBRARIES
        owl::owl
        SOURCES
        deviceCode.cu
)
add_executable(owl_test main.cpp)
target_link_libraries(owl_test
        PRIVATE
        owl_test-ptx
        owl::owl
        stb_image
        owl_viewer
        )