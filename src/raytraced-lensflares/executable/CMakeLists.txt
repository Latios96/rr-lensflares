embed_ptx(
        OUTPUT_TARGET
        raytraced-lensflares-ptx
        PTX_LINK_LIBRARIES
        owl::owl
        SOURCES
        deviceCode.cu
)

add_executable(raytraced-lensflares main.cpp)
target_link_libraries(raytraced-lensflares
        PRIVATE
        raytraced-lensflares-ptx
        owl::owl
        stb_image
        owl_viewer
        raytraced-lensflares-lib
        )

