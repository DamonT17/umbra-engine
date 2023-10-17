//
// Created by Damon Tregear on 10/13/23.
//

#ifndef UMBRAENGINE_POOLALLOCATOR_H
#define UMBRAENGINE_POOLALLOCATOR_H

#include "Allocator.h"

/**
 * @class PoolAllocator
 * @brief A pool allocator.
 *
 * @details This class is a pool allocator. It allocates memory in fixed size blocks. When memory is allocated, a block
 * of the appropriate size is returned. When memory is deallocated, the block is returned to the pool.
 */
class PoolAllocator : public Allocator {
public:
/**
 * @section Constructors
 */

    /**
     * @brief Creates a new pool allocator with the given block size, alignment, allocation size, and starting address.
     */
    PoolAllocator(size_t blockSize, Alignment blockAlignment, size_t sizeBytes, void* start) noexcept;

    /**
     * @brief Copy constructor is deleted.
     */
    PoolAllocator(const PoolAllocator&) = delete;

    /**
     * @brief Copy assignment operator is deleted.
     */
    PoolAllocator& operator=(const PoolAllocator&) = delete;

    /**
     * @brief Move constructor.
     * @param other The pool allocator to move.
     */
    PoolAllocator(PoolAllocator&& other) noexcept;

    /**
     * @brief Move assignment operator.
     * @param other The pool allocator to move.
     * @return A reference to the pool allocator.
     */
    PoolAllocator& operator=(PoolAllocator&& other) noexcept;

    /**
     * @brief Destructor.
     */
    ~PoolAllocator() noexcept override;

/**
 * @section Methods
 * @subsection Public methods
 */

    /**
     * @brief Allocates a block of memory of the given size and alignment.
     * @param sizeBytes The size of the allocation.
     * @param alignment The alignment of the allocation.
     * @return A pointer to the allocated block of memory.
     */
    void* Allocate(const size_t& sizeBytes, Alignment alignment) override;

    /**
     * @brief Frees the given block of memory.
     */
    void Free(void* ptr) noexcept override;

protected:
    /**
     * @brief The size of the blocks.
     */
    size_t blockSize;

    /**
     * @brief The alignment of the blocks.
     */
    Alignment blockAlignment;

    /**
     * @brief The available free blocks.
     */
    void** freeBlocks;
};

#endif //UMBRAENGINE_POOLALLOCATOR_H
