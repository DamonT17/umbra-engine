//
// Created by Damon Tregear on 12/9/2023.
//

#ifndef UMBRAENGINE_MPSCQUEUE_H
#define UMBRAENGINE_MPSCQUEUE_H

#include <atomic>
#include <stdexcept>
#include <vector>

namespace UmbraEngine::DataStructures {

/**
 * @class MpscQueue
 * @brief A lock-free multi-producer single-consumer queue.
 *
 * @details This class is a lock-free multi-producer single-consumer queue. It is designed to be asynchronous,
 * lock-free, and thread-safe. It is implemented using a ring buffer.
 */
template<typename T>
class MpscQueue {
public:
/******************************
 * @section Constructors
 *****************************/
    /**
     * @brief Default constructor (deleted). Creates an empty queue.
     */
    MpscQueue<T>() = delete;

    /**
     * @brief Fill constructor. Creates a queue with the given capacity.
     * @param capacity The capacity of the queue.
     */
    explicit MpscQueue<T>(size_t capacity);

    /**
     * @brief Copy constructor (deleted). Creates a copy of the given queue.
     * @param other The queue to copy.
     */
    MpscQueue<T>(const MpscQueue<T>& other) = delete;

    /**
     * @brief Copy assignment operator (deleted).
     * @param other The queue to copy.
     */
    MpscQueue<T>& operator=(const MpscQueue<T>& other) = delete;

    /**
     * @brief Move constructor (deleted). Moves the given queue.
     * @param other The queue to move.
     */
    MpscQueue<T>(MpscQueue<T>&& other) = delete;

    /**
     * @brief Move assignment operator (deleted).
     */
    MpscQueue<T>& operator=(MpscQueue<T>&& other) = delete;

    /**
     * @brief Destructor.
     */
    ~MpscQueue<T>() noexcept = default;


/******************************
 * @section Methods
 * @subsection Public methods
 *****************************/
    /**
     * @brief Inserts a new element at the end of the queue.
     * @param[in] data The data to insert.
     * @return True if the data was inserted, false otherwise.
     */
    bool Push(const T& data);

    /**
     * @brief Removes the first element of the queue.
     * @return True if the element was removed, false otherwise.
     */
    bool Pop();

    /**
     * @brief Checks if the queue is empty (i.e., its size is zero).
     * @return True if the queue is empty, false otherwise.
     */
    [[nodiscard]] bool Empty() const;

    /**
     * @brief Returns the number of elements in the queue.
     * @return The number of elements in the queue.
     */
    [[nodiscard]] size_t Size() const;

    /**
     * @brief Accesses the first element of the queue.
     * @return The first element of the queue.
     */
    T& Front();

    /**
     * @brief Accesses the last element of the queue.
     * @return The last element of the queue.
     */
    T& Back();

protected:

private:
/******************************
 * @section Properties
 * @subsection Private properties
 *****************************/
    std::atomic<size_t> head_;
    std::atomic<size_t> tail_;

    std::vector<T> buffer_;
    size_t size_;
    size_t capacity_;
};
}

#endif //UMBRAENGINE_MPSCQUEUE_H
