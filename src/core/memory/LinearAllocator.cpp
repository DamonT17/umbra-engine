//
// Created by Damon Tregear on 10/15/23.
//

#include "LinearAllocator.h"

namespace UmbraEngine::Core::Memory {
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

    void* LinearAllocator::Allocate(const size_t& sizeBytes, Alignment alignment) {
        assert(sizeBytes > 0 && alignment > 0);

        // Calculate adjustment needed for alignment
        const uint8_t adjustment = AlignAddressAdjustment(reinterpret_cast<uintptr_t>(position), alignment);

        // Out of memory
        if (usedBytes + sizeBytes + adjustment > size) {
            return nullptr;
        }

        // Align the memory
        void* alignedPosition = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(position) + adjustment);

        position = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(alignedPosition) + sizeBytes);
        usedBytes += sizeBytes + adjustment;
        numAllocations++;

        return alignedPosition;
    }

    void LinearAllocator::Free(void* const ptr) noexcept {
        assert(false && "Use Clear() instead.");
    }

    void LinearAllocator::Clear() noexcept {
        position = start;
        usedBytes = 0;
        numAllocations = 0;
    }

    void* LinearAllocator::GetPosition() const noexcept {
        return position;
    }
}
