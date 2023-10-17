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

StackAllocator::~StackAllocator() noexcept {
    free(start);
    start = nullptr;
}

void* StackAllocator::Allocate(const size_t& sizeBytes, Alignment alignment) {
    assert(sizeBytes > 0 && alignment > 0);

    // Calculate adjustment needed for alignment
    const uint8_t adjustment = AlignAddressAdjustmentWithHeader(reinterpret_cast<uintptr_t>(position), alignment,
                                                                sizeof(Header));

    // Out of memory
    if (usedBytes + sizeBytes + adjustment > size) {
        return nullptr;
    }

    // Align the memory
    void* alignedPosition = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(position) + adjustment);

    // Add the allocation header
    Header* header = reinterpret_cast<Header*>(reinterpret_cast<uintptr_t>(alignedPosition) - sizeof(Header));
    header->adjustment = adjustment;
    header->prevAddress = prevPosition;
    prevPosition = alignedPosition;

    position = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(alignedPosition) + sizeBytes);
    usedBytes += sizeBytes + adjustment;
    numAllocations++;

    return alignedPosition;
}

void StackAllocator::Free(void* ptr) noexcept {
    assert(false && "Use FreeLastBlock() instead.");
}

void StackAllocator::FreeLastBlock() noexcept {
    if (numAllocations == 0) {
        return;
    }

    Header* header = reinterpret_cast<Header*>(reinterpret_cast<uintptr_t>(prevPosition) - sizeof(Header));
    usedBytes -= reinterpret_cast<uintptr_t>(position) - reinterpret_cast<uintptr_t>(prevPosition) + header->adjustment;
    position = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(prevPosition) - header->adjustment);
    prevPosition = header->prevAddress;
    numAllocations--;
}

void StackAllocator::Clear() noexcept {
    position = start;
    usedBytes = 0;
    numAllocations = 0;
}

void* StackAllocator::GetPosition() const noexcept {
    return position;
}
