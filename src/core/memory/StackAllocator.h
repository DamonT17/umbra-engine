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
     * @param sizeBytes The size of the stack allocator.
     */
    explicit StackAllocator(size_t sizeBytes) noexcept;

    /**
     * @brief Creates a new stack allocator with the given size and starting address.
     * @param sizeBytes The size of the allocator.
     * @param start The starting address of the allocator.
     */
    StackAllocator(size_t sizeBytes, void* start) noexcept;

    /**
     * @brief Copy constructor is deleted.
     */
    StackAllocator(const StackAllocator&) = delete;

    /**
     * @brief Copy assignment operator is deleted.
     */
    StackAllocator& operator=(const StackAllocator&) = delete;

    /**
     * @brief Move constructor.
     * @param other The stack allocator to move.
     */
    StackAllocator(StackAllocator&& other) noexcept;

    /**
     * @brief Move assignment operator.
     * @param other The stack allocator to move.
     * @return A reference to the stack allocator.
     */
    StackAllocator& operator=(StackAllocator&& other) noexcept;

    /**
     * @brief Destructor.
     */
    ~StackAllocator() noexcept override;

/**
 * @section Methods
 * @subsection Public methods
 */

    /**
     * @brief Allocates a block of memory of the given size and alignment.
     * @param sizeBytes The size of the block of memory to allocate.
     * @param alignment The alignment of the block of memory to allocate.
     * @return A pointer to the allocated block of memory.
     */
    void* Allocate(const size_t& sizeBytes, Alignment alignment) override;

    /**
     * @brief Frees the given block of memory and resets the marker.
     * @param ptr A pointer to the block of memory to free.
     */
    void Free(void* ptr) noexcept final;

    /**
     * @brief Frees the last allocation and resets the marker.
     */
    void FreeLastBlock() noexcept;

    /**
     * @brief Clears the stack allocator.
     */
    virtual void Clear() noexcept = 0;

    /**
     * @brief Gets the current marker of the stack.
     * @return The current top of the stack.
     */
    [[nodiscard]]
    void* GetPosition() const noexcept;

private:
    /**
     * @brief The current top of the stack.
     */
    void* position;

    /**
     * @brief The previous top of the stack.
     */
    void* prevPosition;

    /**
     * @struct Header
     * @brief The header for each allocation.
     */
    struct Header {
        /**
         * @brief The previous address.
         */
        void* prevAddress;

        /**
         * @brief The adjustment needed for alignment.
         */
        uint8_t adjustment;
    };
};

#endif //UMBRAENGINE_STACKALLOCATOR_H
