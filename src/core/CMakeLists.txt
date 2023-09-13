add_library(core
    core.h
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(math)

target_link_libraries(core math)