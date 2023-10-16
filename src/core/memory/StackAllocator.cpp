//
// Created by Damon Tregear on 10/12/23.
//

#include "StackAllocator.h"

StackAllocator::StackAllocator(const size_t sizeBytes) noexcept : Allocator(sizeBytes) {
    if (start != nullptr) {
        free(start);
    }

    start = malloc(sizeBytes);
    position = start;
}

StackAllocator::StackAllocator(size_t sizeBytes, void *start) noexcept :
        Allocator(sizeBytes, start), position(start) {}

StackAllocator::StackAllocator(StackAllocator&& other) noexcept :
        Allocator(std::move(other)), position(other.position) {
    other.position = nullptr;
}

StackAllocator& StackAllocator::operator=(StackAllocator&& other) noexcept {
    Allocator::operator=(std::move(other));

    position = other.position;
    other.position = nullptr;

    return *this;
}

StackAllocator::~StackAllocator() {
    free(start);
    start = nullptr;
}

// TODO: Verify implementation
void* StackAllocator::Allocate(const size_t& sizeBytes, Alignment alignment) {
    assert(sizeBytes > 0 && alignment > 0);

    // Calculate adjustment needed for alignment
    const size_t adjustment = AlignAddressAdjustment(reinterpret_cast<uintptr_t>(position), alignment);

    // Out of memory
    if (usedBytes + sizeBytes + adjustment > size) {
        return nullptr;
    }

    // Align the memory
    void* alignedPosition = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(position) + adjustment);

    // Update position and usedBytes
    position = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(alignedPosition) + sizeBytes);
    usedBytes += sizeBytes + adjustment;

    // Update markers
    markers[numAllocations++] = usedBytes;

    return alignedPosition;
}

void StackAllocator::Free(void* ptr) noexcept {
    assert(false && "Use FreeLastBlock() instead.");
}

void StackAllocator::FreeLastBlock() noexcept {
    if (numAllocations == 0) {
        return;
    }

    numAllocations--;
    position = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(start) + markers[numAllocations]);
    usedBytes = markers[numAllocations];
}

void StackAllocator::Clear() noexcept {
    position = start;
    usedBytes = 0;
    numAllocations = 0;
}

void* StackAllocator::GetPosition() const noexcept {
    return position;
}
