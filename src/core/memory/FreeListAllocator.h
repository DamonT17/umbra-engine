//
// Created by Damon Tregear on 10/16/23.
//

#ifndef UMBRAENGINE_FREELISTALLOCATOR_H
#define UMBRAENGINE_FREELISTALLOCATOR_H

#include "Allocator.h"

/**
 * @class FreeListAllocator
 * @brief A free list allocator.
 *
 * @details This class is a free list allocator. It allocates memory by maintaining a list of free blocks. When memory
 * is allocated, the allocator searches the free list for a block that is large enough to satisfy the allocation. If
 * the block is larger than the allocation, the block is split into two blocks, one for the allocation and one for the
 * remaining free space. When memory is deallocated, the allocator searches the free list for a block that is adjacent
 * to the deallocated block. If a block is found, the two blocks are merged into a single block.
 */
class FreeListAllocator : public Allocator {
public:
/**
 * @section Constructors
 */

    /**
     * @brief Creates a new free list allocator with the given size and starting address.
     * @param sizeBytes The size of the allocator.
     * @param start The starting address of the allocator.
     */
    FreeListAllocator(size_t sizeBytes, void *start) noexcept;

    /**
     * @brief Copy constructor is deleted.
     */
    FreeListAllocator(const FreeListAllocator&) = delete;

    /**
     * @brief Copy assignment operator is deleted.
     */
    FreeListAllocator& operator=(const FreeListAllocator&) = delete;

    /**
     * @brief Move constructor.
     * @param other The free list allocator to move.
     */
    FreeListAllocator(FreeListAllocator&& other) noexcept;

    /**
     * @brief Move assignment operator.
     * @param other The free list allocator to move.
     * @return A reference to the free list allocator.
     */
    FreeListAllocator& operator=(FreeListAllocator&& other) noexcept;

    /**
     * @brief Destructor.
     */
    ~FreeListAllocator() noexcept override;

/**
 * @section Methods
 * @subsection Public methods
 */

    /**
     * @brief Allocates a block of memory of the given size and alignment.
     * @param sizeBytes The size of the allocation.
     * @param alignment The alignment of the allocation.
     * @return A pointer to the allocated memory.
     */
    void* Allocate(const size_t& sizeBytes, Alignment alignment) override;

    /**
     * @brief Frees the given block of memory
     * @param ptr The block of memory to free.
     */
    void Free(void* ptr) noexcept override;

protected:
    /**
     * @struct Header
     * @brief The header for each allocation.
     */
    struct Header {
        /**
         * @brief The adjustment needed for alignment.
         */
        uint8_t adjustment;

        /**
         * @brief The size of the allocation.
         */
        size_t size;
    };

    /**
     * @struct FreeBlock
     * @brief The header for each free block.
     */
    struct FreeBlock {
        /**
         * @brief The next free block.
         */
        FreeBlock* next;

        /**
         * @brief The size of the free block.
         */
        size_t size;
    };

    /**
     * @brief The list of free memory blocks.
     */
    FreeBlock* freeBlocks;
};

#endif //UMBRAENGINE_FREELISTALLOCATOR_H
