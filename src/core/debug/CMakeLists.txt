add_library(debug
        Logger.cpp
        Logger.h
)

target_include_directories(debug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
