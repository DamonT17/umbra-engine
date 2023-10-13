add_library(memory
        Allocator.h
        MemoryArena.cpp
        MemoryArena.h
        PoolAllocator.cpp
        PoolAllocator.h
        StackAllocator.cpp
        StackAllocator.h
)

target_include_directories(memory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})