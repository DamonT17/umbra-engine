configure_file(config.h.in config.h)

add_subdirectory(adapters)
add_subdirectory(core)
add_subdirectory(data-structures)

target_link_libraries(${PROJECT_NAME}
        adapters
        core
        data-structures
)
