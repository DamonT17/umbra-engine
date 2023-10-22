cmake_minimum_required(VERSION 3.26)
project(UmbraEngine VERSION 0.1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

configure_file(src/config.h.in config.h)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(src/adapters)
add_subdirectory(src/core)

target_link_libraries(${PROJECT_NAME} adapters core)
