//
// Created by Damon Tregear on 10/12/23.
//

#ifndef UMBRAENGINE_STACKALLOCATOR_H
#define UMBRAENGINE_STACKALLOCATOR_H

#include <cstdint>
#include <memory>

#include "Allocator.h"

/**
 * @class StackAllocator
 * @brief A stack allocator.
 *
 * @details This class is a stack allocator. It allocates memory in a stack-like fashion maintaining a pointer, marker,
 * to the top of the stack. When memory is allocated, the marker is incremented by the size of the allocation. When
 * memory is deallocated, the marker is decremented by the size of the previous allocation. This means that memory can
 * only be deallocated in the reverse order that it was allocated in.
 */
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
    void* Allocate(size_t size, Alignment alignment = kALIGN_8) override;

    /**
     * @brief Deallocates the given block of memory.
     * @param ptr A pointer to the block of memory to deallocate.
     */
    void Deallocate(void* ptr) override;

    /**
     * @brief Rolls the stack allocator back to the given marker.
     * @param ptr A pointer to the position to roll back to.
     */
    void Rollback(void* ptr);

    /**
     * @brief Clears the stack allocator.
     */
    void Clear();

private:
    /**
     * @brief The maximum number of allocations that can be tracked by the stack allocator.
     */
    static const uint32_t kMaxAllocations = 256;

    /**
     * @brief The current marker of the stack.
     */
    uint32_t markerIndex;

    /**
     * @brief The maximum size of the stack allocator.
     */
    size_t maxSize;

    /**
     * @brief An array used to store markers for tracking memory allocations.
     */
    size_t markers[kMaxAllocations];

    /**
     * @brief A pointer to the memory block managed by the stack allocator.
     */
    char* memoryBlock;

/**
 * @section Methods
 * @subsection Private methods
 */

    /**
     * @brief Gets the current marker of the stack.
     * @return The current top of the stack.
     */
    size_t GetMarker() const;
};

#endif //UMBRAENGINE_STACKALLOCATOR_H
