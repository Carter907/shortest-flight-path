#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdexcept>
#include <vector>

/**
 * @brief A template implementation of a Min-Priority Queue using a Binary Heap.
 *
 * This class provides a priority queue where the element with the smallest
 * value has the highest priority. It is implemented as a min-heap using a
 * std::vector as the underlying container. This custom implementation is used
 * in place of std::priority_queue.
 *
 * @tparam T The type of elements stored in the priority queue. The type must
 *           support the `operator>` for comparison.
 */
template <typename T> class PriorityQueue {
private:
    std::vector<T> heap;

    /**
     * @brief Calculates the index of the parent of a node.
     * @param i The index of the node.
     * @return int The index of the parent node.
     */
    int parent(int i) { return (i - 1) / 2; }

    /**
     * @brief Calculates the index of the left child of a node.
     * @param i The index of the node.
     * @return int The index of the left child.
     */
    int leftChild(int i) { return (2 * i) + 1; }

    /**
     * @brief Calculates the index of the right child of a node.
     * @param i The index of the node.
     * @return int The index of the right child.
     */
    int rightChild(int i) { return (2 * i) + 2; }

    /**
     * @brief Moves an element up the heap to maintain the heap property.
     *
     * This is used after an element is inserted at the end of the heap. It swaps
     * the element with its parent as long as it is smaller than the parent.
     * @param i The index of the element to move up.
     */
    void heapifyUp(int i) {
        if (i && heap[parent(i)] > heap[i]) {
            std::swap(heap[i], heap[parent(i)]);
            heapifyUp(parent(i));
        }
    }

    /**
     * @brief Moves an element down the heap to maintain the heap property.
     *
     * This is used after the root element is replaced with the last element in the
     * heap. It swaps the element with its smallest child until the heap property
     * is restored.
     * @param i The index of the element to move down.
     */
    void heapifyDown(int i) {
        int left = leftChild(i);
        int right = rightChild(i);
        int smallest = i;

        if (left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    /**
     * @brief Checks if the priority queue is empty.
     * @return bool True if the queue is empty, false otherwise.
     */
    bool isEmpty() const { return heap.empty(); }

    /**
     * @brief Inserts a new element into the priority queue.
     *
     * The element is added to the end of the heap and then moved up to its correct
     * position to maintain the heap property.
     * @param key The element to insert.
     */
    void push(const T &key) {
        heap.push_back(key);
        int index = heap.size() - 1;
        heapifyUp(index);
    }

    /**
     * @brief Removes the smallest element (highest priority) from the queue.
     *
     * The root of the heap is replaced with the last element, and then the new
     * root is moved down to maintain the heap property.
     */
    void pop() {
        if (heap.empty()) {
            return;
        }

        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    /**
     * @brief Accesses the smallest element in the priority queue.
     * @return T The element with the highest priority.
     * @throws std::runtime_error if the priority queue is empty.
     */
    T top() {
        if (heap.empty()) {
            throw std::runtime_error("Priority Queue is empty");
        }
        return heap.front();
    }

    /**
     * @brief Clears all elements from the priority queue.
     */
    void clear() { heap.clear(); }
};

#endif