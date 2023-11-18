//
// Created by Damon Tregear on 10/17/23.
//

#ifndef UMBRAENGINE_STLADAPTER_H
#define UMBRAENGINE_STLADAPTER_H

#include <cstddef>

namespace UmbraEngine::Adapters {
/**
 * @class STLAllocator
 * @brief An adapter class for STL allocators.
 *
 * @tparam T The type of the allocator.
 * @tparam Allocator The allocator to adapt.
 */
template<typename T, class Allocator>
class STLAdapter {
public:
    typedef T value_type;

/******************************
 * @section Constructors
 *****************************/
    STLAdapter() = delete;

    explicit STLAdapter(Allocator& allocator) noexcept: allocator(allocator) {}

    template<typename U>
    explicit STLAdapter(const STLAdapter<U, Allocator>& other) noexcept : allocator(other.allocator) {}

/******************************
 * @section Methods
 * @subsection Public methods
 *****************************/
    [[nodiscard]] constexpr T* Allocate(size_t num);

    constexpr void Free(T* ptr, [[maybe_unused]] size_t num) noexcept;

private:
    Allocator& allocator;
};
}

#endif //UMBRAENGINE_STLADAPTER_H
