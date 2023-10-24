add_library(adapters
        STLAdapter.cpp
        STLAdapter.h
)

target_include_directories(adapters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
