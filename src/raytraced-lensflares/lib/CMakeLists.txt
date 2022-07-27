add_library(raytraced-lensflares-lib
        Geometry.cpp
        Geometry.h
        GlmUtils.h
        GlslShaders.cpp
        GlslShaders.h
        GridGenerator.cpp
        GridGenerator.h
        LensSystem.cpp
        LensSystem.h
        LensSystems.h
        Mesh.h
        Ray.cpp
        Ray.h
        Resources.cpp
        Resources.h
        Utils.cpp
        Utils.h
        )

target_link_libraries(raytraced-lensflares-lib ${CONAN_LIBS} ${CMAKE_DL_LIBS})
target_include_directories(raytraced-lensflares-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})