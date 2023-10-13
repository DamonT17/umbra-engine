//
// Created by Damon Tregear on 10/12/23.
//

#include <memory>

#include "StackAllocator.h"

StackAllocator::StackAllocator(size_t size) : Allocator(size) {
    maxSize = size;
    marker = 0;
    markerIndex = 0;

    memset(&markers, 0, sizeof(size_t) * kMaxAllocations);
}

StackAllocator::~StackAllocator() {
    assert(markerIndex == 0 && marker == 0);
}

void* StackAllocator::Allocate(size_t size, Alignment alignment) {
    // Out of memory
    if (GetCurrentMarker() + size > maxSize) {
        return nullptr;
    }

    // Calculate the next marker
    size_t nextMarker = GetCurrentMarker() + size;

    // Align the memory
    char* alignedAddress = AlignPointer<char>(memoryBlock + nextMarker, alignment);
    nextMarker = alignedAddress - memoryBlock;
    markers[markerIndex++] = nextMarker;

    return memoryBlock + GetCurrentMarker();
}

void StackAllocator::Deallocate(void* ptr) {
    if (markerIndex == 0) {
        return;
    }

    // TODO
}

void StackAllocator::Rollback(void* ptr) {

}

void StackAllocator::Clear() {

}

size_t StackAllocator::GetCurrentMarker() const {
    if (markerIndex == 0) {
        return 0;
    }

    return markers[markerIndex - 1];
}