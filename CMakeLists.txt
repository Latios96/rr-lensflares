cmake_minimum_required(VERSION 3.21)
project(rr-lensflares)

set(CMAKE_CXX_STANDARD 17)

set(CONAN_SYSTEM_INCLUDES ON)
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
        BASIC_SETUP
        BUILD missing
        KEEP_RPATHS)

message("${CONAN_LIBS}")
add_subdirectory(src)