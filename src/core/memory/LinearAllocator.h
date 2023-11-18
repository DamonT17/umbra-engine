//
// Created by Damon Tregear on 10/15/23.
//

#ifndef UMBRAENGINE_LINEARALLOCATOR_H
#define UMBRAENGINE_LINEARALLOCATOR_H

#include <utility>

#include "Allocator.h"

namespace UmbraEngine::Core::Memory {
/**
 * @class LinearAllocator
 * @brief An allocator that allocates memory linearly.
 *
 * @details This class is an allocator that allocates memory linearly. It maintains a pointer to the current position in
 * the memory block. When memory is allocated, the pointer is incremented by the size of the allocation. Freeing
 * arbitrary blocks of memory is not supported. Instead, the allocator provides a Rollback() method that resets the
 * pointer to a previous position. This allows for the deallocation of all memory allocated after the given position.
 */
class LinearAllocator : public Allocator {
public:
/******************************
 * @section Constructors
 *****************************/
    /**
     * @brief Creates a new linear allocator with the given size and starting address.
     * @param sizeBytes The size of the allocator.
     * @param start The starting address of the allocator.
     */
    LinearAllocator(size_t sizeBytes, void* start) noexcept;

    /**
     * @brief Copy constructor is deleted.
     */
    LinearAllocator(const LinearAllocator&) = delete;

    /**
     * @brief Copy assignment operator is deleted.
     */
    LinearAllocator& operator=(const LinearAllocator&) = delete;

    /**
     * @brief Move constructor.
     * @param other The linear allocator to move.
     */
    LinearAllocator(LinearAllocator&& other) noexcept;

    /**
     * @brief Move assignment operator.
     * @param other The linear allocator to move.
     * @return A reference to the linear allocator.
     */
    LinearAllocator& operator=(LinearAllocator&& other) noexcept;

    /**
     * @brief Destructor.
     */
    ~LinearAllocator() noexcept override;

/******************************
 * @section Methods
 * @subsection Public methods
 *****************************/
    /**
     * @brief Allocates memory of the given sizeBytes and alignment.
     * @param sizeBytes The sizeBytes of the allocation.
     * @param alignment The alignment of the allocation.
     * @return A pointer to the allocated memory.
     */
    void* Allocate(const size_t& sizeBytes, Alignment alignment) override;

    /**
     * @brief Frees the given block of memory.
     * @param ptr The block of memory to free.
     *
     * @details This method is not supported by the linear allocator. Instead, use Rollback() or Clear() to free
     * memory.
     */
    void Free(void* ptr) noexcept final;

    /**
     * @brief Frees all memory allocated by the allocator.
     */
    virtual void Clear() noexcept = 0;

    /**
     * @brief Gets the current position of the allocator.
     * @return The current position of the allocator.
     */
    [[nodiscard]]
    void* GetPosition() const noexcept;

protected:
    /**
     * @brief The current position of the allocator.
     */
    void* position;
};
}

#endif //UMBRAENGINE_LINEARALLOCATOR_H
