//
// Created by Damon Tregear on 10/12/23.
//

#ifndef UMBRAENGINE_ALLOCATOR_H
#define UMBRAENGINE_ALLOCATOR_H

#include <cassert>
#include <cstddef>
#include <cstdint>

#define KB(x) ((uint64_t) x * (uint64_t) 0x400)
#define MB(x) ((uint64_t) x * (uint64_t) 0x100000)
#define GB(x) ((uint64_t) x * (uint64_t) 0x40000000)

/**
 * @enum Alignment
 * @brief An enumeration of possible alignments for memory allocations.
 *
 * @details This enumeration provides a list of possible alignments for memory allocations. It is used by allocators to
 * determine how to align memory allocations.
 */
enum Alignment : uint32_t {
    kALIGN_NONE = 0x00,
    kALIGN_4 = 0x04,
    kALIGN_8 = 0x08,
    kALIGN_16 = 0x10,
    kALIGN_32 = 0x20
};

/**
 * @brief Aligns the given address to the given alignment.
 * @param address The address to align.
 * @param alignment The alignment to align the address to.
 * @return The aligned address.
 */
inline uintptr_t AlignAddress(uintptr_t address, Alignment alignment) {
    const size_t mask = alignment - 1;
    assert((alignment & mask) == 0);    // Power of 2

    return address + mask & ~mask;
}

/**
 * @brief Aligns the given pointer to the given alignment.
 * @param ptr The pointer to align.
 * @param alignment The alignment to align the pointer to.
 * @return The aligned pointer.
 */
template <typename T>
inline T* AlignPointer(T* ptr, Alignment alignment) {
    const uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
    const uintptr_t addressAligned = AlignAddress(address, alignment);

    return reinterpret_cast<T*>(addressAligned);
}

/**
 * @class Allocator
 * @brief An abstract base class for memory allocators.
 *
 * @details This class is an abstract base class for memory allocators. It provides a common interface for allocating
 * and deallocating memory. It also provides a common interface for getting the size of an allocation and the total
 * amount of memory allocated.
 */
class Allocator {
public:
/**
 * @section Constructors
 */

    /**
     * @brief Creates a new allocator with the given size.
     * @param size The size of the allocator.
     */
    explicit Allocator(size_t size) : size(size) {}

    /**
     * @brief Destroys the allocator.
     */
    virtual ~Allocator() {}

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
    virtual void* Allocate(size_t size, Alignment alignment = kALIGN_NONE) = 0;

    /**
     * @brief Deallocates the given block of memory.
     * @param ptr A pointer to the block of memory to deallocate.
     */
    virtual void Deallocate(void* ptr) = 0;

protected:
/**
 * @section Properties
 * @subsection Protected properties
 */

    /**
     * @property size
     * @brief The size of the allocator.
     */
    size_t size;
};

#endif //UMBRAENGINE_ALLOCATOR_H
