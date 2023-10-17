//
// Created by Damon Tregear on 10/13/23.
//

#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(size_t blockSize, Alignment blockAlignment, size_t sizeBytes, void *start) noexcept :
        Allocator(sizeBytes, start), blockSize(blockSize), blockAlignment(blockAlignment) {
    assert(blockSize >= sizeof(void*));

    // Calculate adjustment needed to keep blocks correctly aligned
    const uint8_t adjustment = AlignAddressAdjustment(reinterpret_cast<uintptr_t>(start),
                                                      blockAlignment);
    freeBlocks = reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(start) + adjustment);

    // Initialize free blocks list
    size_t numBlocks = (sizeBytes - adjustment) / blockSize;
    void** ptr = freeBlocks;
    for (size_t i = 0; i < numBlocks - 1; ++i) {
        *ptr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr) + blockSize);
        ptr = reinterpret_cast<void**>(*ptr);
    }

    *ptr = nullptr;
}

PoolAllocator::PoolAllocator(PoolAllocator&& other) noexcept :
        Allocator(std::move(other)), blockSize(other.blockSize), blockAlignment(other.blockAlignment),
        freeBlocks(other.freeBlocks) {
    other.freeBlocks = nullptr;
}

PoolAllocator& PoolAllocator::operator=(PoolAllocator&& other) noexcept {
    Allocator::operator=(std::move(other));

    blockSize = other.blockSize;
    blockAlignment = other.blockAlignment;
    freeBlocks = other.freeBlocks;
    other.freeBlocks = nullptr;

    return *this;
}

PoolAllocator::~PoolAllocator() noexcept {
    free(start);
    start = nullptr;
    freeBlocks = nullptr;
}

void* PoolAllocator::Allocate(const size_t& sizeBytes, Alignment alignment) {
    assert(sizeBytes == blockSize && alignment == blockAlignment);

    // If no free blocks, return nullptr
    if (freeBlocks == nullptr) {
        return nullptr;
    }

    // Get first free block
    void* ptr = freeBlocks;
    freeBlocks = (void**) *freeBlocks;
    usedBytes += sizeBytes;
    numAllocations++;

    return ptr;
}

void PoolAllocator::Free(void *ptr) noexcept {
    *((void**) ptr) = freeBlocks;
    freeBlocks = (void**) ptr;
    usedBytes -= blockSize;
    numAllocations--;
}
