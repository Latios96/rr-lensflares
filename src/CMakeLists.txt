embed_ptx(
        OUTPUT_TARGET
        owl_test-ptx
        PTX_LINK_LIBRARIES
        owl::owl
        SOURCES
        deviceCode.cu
)
add_executable(owl_test main.cpp LensSystem.h LensSystem.cpp LensSystems.h)
target_link_libraries(owl_test
        PRIVATE
        owl_test-ptx
        owl::owl
        stb_image
        owl_viewer
        )