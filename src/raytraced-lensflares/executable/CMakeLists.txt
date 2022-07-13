add_executable(raytraced-lensflares
        main.cpp
        )
target_link_libraries(raytraced-lensflares
        PUBLIC
        imgui
        raytraced-lensflares-lib
        ${CONAN_LIBS}
        ${CMAKE_DL_LIBS}
        )

add_custom_command(TARGET raytraced-lensflares PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shader ${CMAKE_BINARY_DIR}/bin/shader)