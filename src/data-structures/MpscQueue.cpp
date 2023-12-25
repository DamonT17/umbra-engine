//
// Created by Damon Tregear on 12/9/2023.
//

#include "MpscQueue.h"

namespace UmbraEngine::DataStructures {
/******************************
 * @section Constructors
 *****************************/
template<typename T>
MpscQueue<T>::MpscQueue(size_t capacity) : head_(0), tail_(0), size_(0), capacity_(capacity), buffer_(capacity) {}

// TODO: Add the destructor?

/******************************
 * @section Methods
 * @subsection Public methods
 *****************************/
template<typename T>
bool MpscQueue<T>::Push(const T& data) {
    size_t newTail = (tail_.load(std::memory_order_relaxed) + 1) % capacity_;
    if (newTail == head_.load(std::memory_order_acquire)) {
        return false;
    }

    buffer_[tail_] = data;
    tail_.store(newTail, std::memory_order_release);
    size_++;

    return true;
}

template<typename T>
bool MpscQueue<T>::Pop() {
    size_t newHead = (head_.load(std::memory_order_acquire) + 1) % capacity_;
    if (newHead == tail_.load(std::memory_order_relaxed)) {
        return false;
    }

    head_.store(newHead, std::memory_order_release);
    size_--;

    return true;
}

template<typename T>
bool MpscQueue<T>::Empty() const {
    return size_ == 0;
}

template<typename T>
size_t MpscQueue<T>::Size() const {
    return (tail_.load(std::memory_order_relaxed) - head_.load(std::memory_order_relaxed)) % capacity_;
}

template<typename T>
T& MpscQueue<T>::Front() {
    if (Empty()) {
        throw std::runtime_error("Queue is empty");
    }

    return buffer_[head_.load(std::memory_order_relaxed)];
}

template<typename T>
T& MpscQueue<T>::Back() {
    if (Empty()) {
        throw std::runtime_error("Queue is empty");
    }

    return buffer_[(tail_.load(std::memory_order_relaxed) - 1) % capacity_];
}

}
