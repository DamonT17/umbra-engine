//
// Created by Damon Tregear on 10/16/23.
//

#include "FreeListAllocator.h"

namespace UmbraEngine::Core::Memory {
    FreeListAllocator::FreeListAllocator(size_t sizeBytes, void* start) noexcept :
            Allocator(sizeBytes, start), freeBlocks(reinterpret_cast<FreeBlock*>(start)) {
        assert(sizeBytes > sizeof(FreeBlock));

        freeBlocks->size = sizeBytes;
        freeBlocks->next = nullptr;
    }

    FreeListAllocator::FreeListAllocator(FreeListAllocator&& other) noexcept :
            Allocator(std::move(other)), freeBlocks(other.freeBlocks) {
        other.freeBlocks = nullptr;
    }

    FreeListAllocator& FreeListAllocator::operator=(FreeListAllocator&& other) noexcept {
        Allocator::operator=(std::move(other));

        freeBlocks = other.freeBlocks;
        other.freeBlocks = nullptr;

        return *this;
    }

    FreeListAllocator::~FreeListAllocator() noexcept {
        free(start);
        start = nullptr;
        freeBlocks = nullptr;
    }

    void* FreeListAllocator::Allocate(const size_t& sizeBytes, Alignment alignment) {
        assert(sizeBytes > 0 && alignment > 0);

        FreeBlock* prevFreeBlock = nullptr;
        FreeBlock* freeBlock = freeBlocks;

        FreeBlock* prevBestFit = nullptr;
        FreeBlock* bestFit = nullptr;

        uint8_t bestFitAdjustment = 0;
        size_t bestFitTotalSize = 0;

        while (freeBlock != nullptr) {
            // Calculate adjustment needed to keep object correctly aligned
            const uint8_t adjustment = AlignAddressAdjustmentWithHeader(reinterpret_cast<uintptr_t>(freeBlock),
                                                                        alignment, sizeof(Header));
            size_t totalSize = sizeBytes + adjustment;

            // If allocation doesn't fit in this FreeBlock, try the next
            if (freeBlock->size > totalSize && (bestFit == nullptr || freeBlock->size < bestFit->size)) {
                prevBestFit = prevFreeBlock;
                bestFit = freeBlock;
                bestFitAdjustment = adjustment;
                bestFitTotalSize = totalSize;

                // If it fits perfectly, break
                if (freeBlock->size == totalSize) {
                    break;
                }
            }

            prevFreeBlock = freeBlock;
            freeBlock = freeBlock->next;
        }

        // Failed to find a free block that fits
        if (bestFit == nullptr) {
            throw std::bad_alloc();
        }

        // Free block cannot be split into two blocks (no space for header)
        if (bestFit->size - bestFitTotalSize <= sizeof(Header)) {
            bestFitTotalSize = bestFit->size;   // Allocate the entire block

            // Remove the free block from the free list
            if (prevBestFit != nullptr) {
                prevBestFit->next = bestFit->next;
            } else {
                freeBlocks = bestFit->next;
            }
        } else {  // Split the free block into two blocks (free and allocated)
            FreeBlock* newBlock = reinterpret_cast<FreeBlock*>(reinterpret_cast<uintptr_t>(bestFit) + bestFitTotalSize);
            newBlock->size = bestFit->size - bestFitTotalSize;
            newBlock->next = bestFit->next;

            // Insert new block into the free list
            if (prevBestFit != nullptr) {
                prevBestFit->next = newBlock;
            } else {
                freeBlocks = newBlock;
            }
        }

        // Align the memory
        void* alignedPosition = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(bestFit) + bestFitAdjustment);

        // Add the allocation header
        Header* header = reinterpret_cast<Header*>(reinterpret_cast<uintptr_t>(alignedPosition) - sizeof(Header));
        header->size = bestFitTotalSize;
        header->adjustment = bestFitAdjustment;

        usedBytes += bestFitTotalSize;
        numAllocations++;

        return alignedPosition;
    }

    void FreeListAllocator::Free(void* ptr) noexcept {
        assert(ptr != nullptr);

        // Retrieve the allocation header from the previous byte prior to the given pointer
        Header* header = reinterpret_cast<Header*>(reinterpret_cast<uintptr_t>(ptr) - sizeof(Header));

        // Retrieve the free block from the header
        uintptr_t blockStart = reinterpret_cast<uintptr_t>(ptr) - header->adjustment;
        size_t blockSize = header->size;
        uintptr_t blockEnd = blockStart + blockSize;

        FreeBlock* prevFreeBlock = nullptr;
        FreeBlock* freeBlock = freeBlocks;

        // Find the correct place to insert the free block
        while (freeBlock != nullptr) {
            if (reinterpret_cast<uintptr_t>(freeBlock) >= blockEnd) {
                break;
            }

            prevFreeBlock = freeBlock;
            freeBlock = freeBlock->next;
        }

        // Case 1: No free blocks before this one
        if (prevFreeBlock == nullptr) {
            prevFreeBlock = reinterpret_cast<FreeBlock*>(blockStart);
            prevFreeBlock->size = blockSize;
            prevFreeBlock->next = freeBlocks;

            freeBlocks = prevFreeBlock;
        } else if (reinterpret_cast<uintptr_t>(prevFreeBlock) + prevFreeBlock->size == blockStart) {
            // Case 2: Free block before this one
            prevFreeBlock->size += blockSize;
        } else {
            // Case 3: Free block after this one
            FreeBlock* tempBlock = reinterpret_cast<FreeBlock*>(blockStart);
            tempBlock->size = blockSize;
            tempBlock->next = prevFreeBlock->next;

            prevFreeBlock->next = tempBlock;
            prevFreeBlock = tempBlock;
        }

        // Merge free blocks
        if (reinterpret_cast<uintptr_t>(prevFreeBlock) + prevFreeBlock->size ==
            reinterpret_cast<uintptr_t>(prevFreeBlock->next)) {
            prevFreeBlock->size += prevFreeBlock->next->size;
            prevFreeBlock->next = prevFreeBlock->next->next;
        }

        usedBytes -= blockSize;
        numAllocations--;
    }
}
