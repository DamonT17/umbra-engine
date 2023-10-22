//
// Created by Damon Tregear on 10/17/23.
//

#ifndef UMBRAENGINE_STLADAPTER_H
#define UMBRAENGINE_STLADAPTER_H

#include "../core/memory/Allocator.h"

namespace UmbraEngine::Adapters {
    template<typename T, class Allocator>
    class STLAdapter {
    public:
        using valueType = T;

    /**
     * @section Constructors
     */

        STLAdapter() = delete;

        explicit STLAdapter(Allocator &allocator) noexcept: allocator(allocator) {}

        template<typename U>
        STLAdapter(const STLAdapter<U, Allocator> &other) noexcept : allocator(other.allocator) {}

    /**
     * @section Methods
     * @subsection Public methods
     */

        [[nodiscard]] constexpr T *Allocate(const size_t num);

        constexpr void Free(T *const ptr, const size_t num) noexcept;

    private:
        Allocator &allocator;
    };

    template<typename T>
    using FreeListAdapter = STLAdapter<T, FreeListAllocator>;

    template<typename T>
    using LinearAdapter = STLAdapter<T, LinearAllocator>;

    template<typename T>
    using StackAdapter = STLAdapter<T, StackAllocator>;

    template<typename T>
    using PoolAdapter = STLAdapter<T, PoolAllocator>;
}

#endif //UMBRAENGINE_STLADAPTER_H
