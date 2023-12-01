add_library(core
        Core.h
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(debug)
add_subdirectory(math)
add_subdirectory(memory)

target_link_libraries(core
        debug
        math
        memory
)
