add_library(raytraced-lensflares-lib
        LensSystem.h
        LensSystem.cpp
        LensSystems.h)

target_link_libraries(raytraced-lensflares-lib
        PUBLIC owl::owl
        )
target_include_directories(raytraced-lensflares-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})