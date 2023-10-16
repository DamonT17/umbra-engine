//
// Created by Damon Tregear on 10/15/23.
//

#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(const size_t sizeBytes, void* const start) noexcept :
        Allocator(sizeBytes, start), position(start) {}

LinearAllocator::LinearAllocator(LinearAllocator&& other) noexcept :
        Allocator(std::move(other)), position(other.position) {
    other.position = nullptr;
}

LinearAllocator& LinearAllocator::operator=(LinearAllocator&& other) noexcept {
    Allocator::operator=(std::move(other));

    position = other.position;
    other.position = nullptr;

    return *this;
}

LinearAllocator::~LinearAllocator() noexcept {
    free(start);
    start = nullptr;
}

void* LinearAllocator::Allocate(const size_t& size, Alignment alignment) {
    assert(size > 0 && alignment > 0);

    // Align the memory
    position = AlignPointer(position, alignment);
    usedBytes = reinterpret_cast<uintptr_t>(position) - reinterpret_cast<uintptr_t>(start);
    ++numAllocations;

    return position;
}

void LinearAllocator::Free(void* const ptr) noexcept {
    assert(false && "Use Rollback() instead.");
}

void LinearAllocator::Rollback(void* const marker) noexcept {
    assert(position >= marker && start <= marker);

    position = marker;
    usedBytes = reinterpret_cast<uintptr_t>(position) - reinterpret_cast<uintptr_t>(start);
}

void LinearAllocator::Clear() noexcept {
    position = start;
    usedBytes = 0;
    numAllocations = 0;
}

void* LinearAllocator::GetPosition() const noexcept {
    return position;
}

