add_library(math
    Matrix.cpp
    Matrix.h
    Vector2.cpp
    Vector2.h
    Vector3.cpp
    Vector3.h
    Vector4.cpp
    Vector4.h
)

target_include_directories(math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})