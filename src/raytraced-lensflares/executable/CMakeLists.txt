add_executable(raytraced-lensflares
        main.cpp
        UiControls.h
        )
target_link_libraries(raytraced-lensflares
        PUBLIC
        imgui
        raytraced-lensflares-lib
        ${CONAN_LIBS}
        ${CMAKE_DL_LIBS}
        )

add_custom_target(copy-shaders ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shader
        ${CMAKE_BINARY_DIR}/bin/shader
        )
add_dependencies(raytraced-lensflares copy-shaders)

add_custom_target(copy-meshes ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/meshes
        ${CMAKE_BINARY_DIR}/bin/meshes
        )
add_dependencies(raytraced-lensflares copy-meshes)

add_custom_target(copy-textures ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/textures
        ${CMAKE_BINARY_DIR}/bin/textures
        )
add_dependencies(raytraced-lensflares copy-textures)

install(TARGETS raytraced-lensflares DESTINATION bin)