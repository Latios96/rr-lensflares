add_executable(rr-lensflares-tests
        main.cpp
        TestLensSystem.cpp
        GlmCatchUtils.h
        )
target_link_libraries(rr-lensflares-tests PUBLIC
        raytraced-lensflares-lib
        )

add_test(
        NAME rr-lensflares-tests
        COMMAND rr-lensflares-tests --durations yes)