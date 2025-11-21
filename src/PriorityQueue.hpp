#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdexcept>
#include <vector>

// A custom template implementation of a Min-Priority Queue using a Binary Heap.
// This is required because the prompt forbids std::priority_queue.
template <typename T> class PriorityQueue {
private:
  std::vector<T> heap;

  // Helper to get parent index
  int parent(int i) { return (i - 1) / 2; }

  // Helper to get left child index
  int leftChild(int i) { return (2 * i) + 1; }

  // Helper to get right child index
  int rightChild(int i) { return (2 * i) + 2; }

  // Move an element up to maintain heap property
  void heapifyUp(int i) {
    if (i && heap[parent(i)] > heap[i]) {
      std::swap(heap[i], heap[parent(i)]);
      heapifyUp(parent(i));
    }
  }

  // Move an element down to maintain heap property
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
  // Check if queue is empty
  bool isEmpty() const { return heap.empty(); }

  // Insert a new element
  void push(const T &key) {
    heap.push_back(key);
    int index = heap.size() - 1;
    heapifyUp(index);
  }

  // Remove the smallest element
  void pop() {
    if (heap.empty()) {
      return;
    }

    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
  }

  // Access the smallest element
  T top() {
    if (heap.empty()) {
      throw std::runtime_error("Priority Queue is empty");
    }
    return heap.front();
  }

  // Clear the queue
  void clear() { heap.clear(); }
};

#endif
