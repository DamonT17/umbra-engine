add_library(data-structures
        MpscQueue.cpp
        MpscQueue.h
)

target_include_directories(data-structures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
