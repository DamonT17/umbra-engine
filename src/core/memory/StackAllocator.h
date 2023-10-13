//
// Created by Damon Tregear on 10/12/23.
//

#ifndef UMBRAENGINE_STACKALLOCATOR_H
#define UMBRAENGINE_STACKALLOCATOR_H

#include <cstdint>

#include "Allocator.h"

class StackAllocator : public Allocator {
public:
/**
 * @section Constructors
 */

    /**
     * @brief Creates a new stack allocator with the given size.
     * @param size The size of the stack allocator.
     */
    explicit StackAllocator(size_t size);

    /**
     * @brief Destroys the stack allocator.
     */
    ~StackAllocator() override;

/**
 * @section Methods
 * @subsection Public methods
 */

    /**
     * @brief Allocates a block of memory of the given size and alignment.
     * @param size The size of the block of memory to allocate.
     * @param alignment The alignment of the block of memory to allocate.
     * @return A pointer to the allocated block of memory.
     */
    void* Allocate(size_t size, Alignment alignment = kALIGN_4) override;

    /**
     * @brief Deallocates the given block of memory.
     * @param ptr A pointer to the block of memory to deallocate.
     */
    void Deallocate(void* ptr) override;

    /**
     * @brief Rolls the stack allocator back to the given pointer.
     * @param ptr A pointer to the point to roll back to.
     */
    void Rollback(void* ptr);

    /**
     * @brief Clears the stack allocator.
     */
    void Clear();

private:
    static const uint32_t kMaxAllocations = 256;
    uint32_t markerIndex;
    size_t maxSize;
    size_t marker;
    size_t markers[kMaxAllocations];

    char* memoryBlock;

/**
 * @section Methods
 * @subsection Private methods
 */

    /**
     * @brief Gets the current marker of the stack.
     * @return The current top of the stack.
     */
    size_t GetCurrentMarker() const;
};

#endif //UMBRAENGINE_STACKALLOCATOR_H
