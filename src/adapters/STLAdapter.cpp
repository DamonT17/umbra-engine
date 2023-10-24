//
// Created by Damon Tregear on 10/17/23.
//

#include "STLAdapter.h"

namespace UmbraEngine::Adapters {
    template<typename T, class Allocator>
    [[nodiscard]] constexpr T* STLAdapter<T, Allocator>::Allocate(const size_t num) {
        return allocator.Allocate(num * sizeof(T), alignof(T));
    }

    template<typename T, class Allocator>
    constexpr void STLAdapter<T, Allocator>::Free(T* const ptr, [[maybe_unused]] const size_t num) noexcept {
        allocator.Free(ptr);
    }
}
