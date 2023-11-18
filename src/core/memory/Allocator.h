//
// Created by Damon Tregear on 10/12/23.
//

#ifndef UMBRAENGINE_ALLOCATOR_H
#define UMBRAENGINE_ALLOCATOR_H

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>

namespace UmbraEngine::Core::Memory {
#define KB(x) ((uint64_t) x * (uint64_t) 0x400)
#define MB(x) ((uint64_t) x * (uint64_t) 0x100000)
#define GB(x) ((uint64_t) x * (uint64_t) 0x40000000)

/**
 * @enum Alignment
 * @brief An enumeration of possible alignments for memory allocations.
 *
 * @details This enumeration provides a list of possible alignments for memory allocations. It is used by allocators
 * to determine how to align memory allocations.
 */
enum Alignment : uint8_t {
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
    const size_t mask = alignment - 1u;
    assert((alignment & mask) == 0);    // Power of 2

    return address + mask & ~mask;
}

/**
 * @brief Calculates the adjustment needed to align the given address to the given alignment.
 * @param address The address to align.
 * @param alignment The alignment to align the address to.
 * @return The adjustment needed to align the given address to the given alignment.
 */
inline uint8_t AlignAddressAdjustment(uintptr_t address, Alignment alignment) {
    const size_t mask = alignment - 1u;
    assert((alignment & mask) == 0);    // Power of 2

    uint8_t adjustment = alignment - (address & mask);
    if (adjustment == alignment) {
        return 0;
    }

    return adjustment;
}

/**
 * @brief Calculates the adjustment needed to align the given address to the given alignment and header size.
 * @param address The address to align.
 * @param alignment The alignment to align the address to.
 * @param headerSize The size of the header.
 * @return The adjustment needed to align the given address to the given alignment and header size.
 */
inline uint8_t AlignAddressAdjustmentWithHeader(uintptr_t address, Alignment alignment, uint8_t headerSize) {
    uint8_t adjustment = AlignAddressAdjustment(address, alignment);
    uint8_t neededSpace = headerSize;
    if (adjustment < neededSpace) {
        neededSpace -= adjustment;
        adjustment += alignment * (neededSpace / alignment);

        if (neededSpace % alignment > 0) {
            adjustment += alignment;
        }
    }

    return adjustment;
}

/**
 * @brief Aligns the given pointer to the given alignment.
 * @param ptr The pointer to align.
 * @param alignment The alignment to align the pointer to.
 * @return The aligned pointer.
 */
template<typename T>
inline T* AlignPointer(T* ptr, Alignment alignment) {
    const uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
    const uintptr_t addressAligned = AlignAddress(address, alignment);

    return reinterpret_cast<T*>(addressAligned);
}

/**
 * @class Allocator
 * @brief An abstract base class for memory allocators.
 *
 * @details This class is an abstract base class for memory allocators. It provides a common interface for
 * allocating and deallocating memory. It also provides a common interface for getting the size of an allocation
 * and the total amount of memory allocated.
 */
class Allocator {
public:
/******************************
 * @section Constructors
 *****************************/
    /**
     * @brief Creates a new allocator with the given size.
     * @param sizeBytes The size of the allocator.
     */
    explicit Allocator(const size_t sizeBytes) noexcept :
            size(sizeBytes), usedBytes(0), numAllocations(0), start(nullptr) {
        assert(sizeBytes > 0);
    }

    /**
     * @brief Creates a new allocator with the given size and starting address.
     * @param sizeBytes The size of the allocator.
     * @param start The starting address of the allocator.
     */
    Allocator(const size_t sizeBytes, void* const start) noexcept :
            size(sizeBytes), usedBytes(0), numAllocations(0), start(start) {
        assert(sizeBytes > 0);
    }

    /**
     * @brief Copy constructor is deleted.
     */
    Allocator(const Allocator&) = delete;

    /**
     * @brief Copy assignment operator is deleted.
     */
    Allocator& operator=(const Allocator&) = delete;

    /**
     * @brief Move constructor.
     * @param other The allocator to move.
     */
    Allocator(Allocator&& other) noexcept :
            size(other.size), usedBytes(other.usedBytes), numAllocations(other.numAllocations), start(other.start) {
        other.size = 0;
        other.usedBytes = 0;
        other.numAllocations = 0;
        other.start = nullptr;
    }

    /**
     * @brief Move assignment operator.
     * @param other The allocator to move.
     * @return A reference to the allocator.
     */
    Allocator& operator=(Allocator&& other) noexcept {
        size = other.size;
        usedBytes = other.usedBytes;
        numAllocations = other.numAllocations;
        start = other.start;

        other.size = 0;
        other.usedBytes = 0;
        other.numAllocations = 0;
        other.start = nullptr;

        return *this;
    }

    /**
     * @brief Destroys the allocator.
     */
    virtual ~Allocator() noexcept {
        assert(numAllocations == 0 && usedBytes == 0);

        start = nullptr;
        size = 0;
    }

/******************************
 * @section Methods
 * @subsection Public methods
 *****************************/
    /**
     * @brief Allocates a block of memory of the given size and alignment.
     * @param size The size of the block of memory to allocate.
     * @param alignment The alignment of the block of memory to allocate.
     * @return A pointer to the allocated block of memory.
     */
    virtual void* Allocate(const size_t& size, const Alignment alignment) = 0;

    /**
     * @brief Frees the given block of memory.
     */
    virtual void Free(void* const ptr) = 0;

    /**
     * @brief Gets the size of the allocator.
     * @return The size of the allocator.
     */
    const size_t& GetSize() const noexcept {
        return size;
    }

    /**
     * @brief Gets the number of bytes used by the allocator.
     * @return The number of bytes used by the allocator.
     */
    const size_t& GetUsed() const noexcept {
        return usedBytes;
    }

    /**
     * @brief Gets the number of allocations made by the allocator.
     * @return The number of allocations made by the allocator.
     */
    const size_t& GetNumAllocations() const noexcept {
        return numAllocations;
    }

    /**
     * @brief Gets the starting address of the allocator.
     * @return The starting address of the allocator.
     */
    const void* GetStart() const noexcept {
        return start;
    }

protected:
/******************************
 * @section Properties
 * @subsection Protected properties
 *****************************/
    /**
     * @property start
     * @brief The starting address of the allocator.
     */
    void* start;

    /**
     * @property size
     * @brief The size of the allocator.
     */
    size_t size;

    /**
     * @property usedBytes
     * @brief The number of bytes used by the allocator.
     */
    size_t usedBytes;

    /**
     * @property numAllocations
     * @brief The number of allocations made by the allocator.
     */
    size_t numAllocations;
};
}

#endif //UMBRAENGINE_ALLOCATOR_H
