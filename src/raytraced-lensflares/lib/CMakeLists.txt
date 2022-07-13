add_library(raytraced-lensflares-lib
        LensSystem.h
        LensSystem.cpp
        LensSystems.h
        Geometry.cpp
        Geometry.h
        GlslShaders.cpp
        GlslShaders.h
        Utils.cpp
        Utils.h
        )

target_link_libraries(raytraced-lensflares-lib ${CONAN_LIBS} ${CMAKE_DL_LIBS})
target_include_directories(raytraced-lensflares-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})