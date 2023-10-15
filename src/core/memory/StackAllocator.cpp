//
// Created by Damon Tregear on 10/12/23.
//

#include "StackAllocator.h"

StackAllocator::StackAllocator(size_t size) : Allocator(size) {
    memoryBlock = reinterpret_cast<char*>(malloc(size));
    maxSize = size;
    markerIndex = 0;

    memset(&markers, 0, sizeof(size_t) * kMaxAllocations);
}

StackAllocator::~StackAllocator() {
    free(memoryBlock);
}

void* StackAllocator::Allocate(size_t size, Alignment alignment) {
    // Out of memory
    if (GetMarker() + size > maxSize) {
        return nullptr;
    }

    // Calculate the next marker
    size_t nextMarker = GetMarker() + size;

    // Align the memory
    char* alignedAddress = AlignPointer<char>(memoryBlock + nextMarker, alignment);
    nextMarker = alignedAddress - memoryBlock;
    markers[markerIndex++] = nextMarker;

    return memoryBlock + GetMarker();
}

void StackAllocator::Deallocate(void *ptr) {
    assert(ptr >= memoryBlock && ptr <= memoryBlock + maxSize);

    size_t marker = reinterpret_cast<char*>(ptr) - memoryBlock;

    // Zero the memory
    memset(memoryBlock + marker, 0, maxSize - marker);

    // Reset the marker
    while (markerIndex > 0 && markers[markerIndex - 1] >= marker) {
        --markerIndex;
    }
}

void StackAllocator::Rollback(void* ptr) {
    assert(ptr >= memoryBlock && ptr <= memoryBlock + maxSize);

    size_t marker = reinterpret_cast<char*>(ptr) - memoryBlock;
    while (markerIndex > 0 && markers[markerIndex - 1] > marker) {
        --markerIndex;
    }
}

void StackAllocator::Clear() {
    markerIndex = 0;
}

size_t StackAllocator::GetMarker() const {
    if (markerIndex == 0) {
        return 0;
    }

    return markers[markerIndex - 1];
}
