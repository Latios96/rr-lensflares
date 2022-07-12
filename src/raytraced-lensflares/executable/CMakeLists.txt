add_executable(raytraced-lensflares main.cpp)
target_link_libraries(raytraced-lensflares
        PUBLIC
        ${CONAN_LIBS}
        ${CMAKE_DL_LIBS}
        )