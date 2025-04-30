//
// Created by User on 29.04.2025.
//

#ifndef SRC_NODE_H
#define SRC_NODE_H

#include <vector>
#include <memory>
#include <mutex>
#include <atomic>

template <typename T>
class Node {
public:
    using Ptr = std::shared_ptr<Node<T>>;
    using WeakPtr = std::weak_ptr<Node<T>>;
private:
    T data;
    std::vector<Ptr> neighbors;
    mutable std::mutex mutex_;
    std::atomic<bool> visited;
public:


    explicit Node(const T& value)
            : data(value), visited(false) {}

    T& getData() { return data; }
    const T& getData() const { return data; }

    void addNeighbor(const Ptr& neighbor) {
        std::lock_guard<std::mutex> lock(mutex_);
        neighbors.push_back(neighbor);
    }

    std::vector<Ptr> getNeighbors() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return neighbors;
    }

    void markVisited() {
        visited.store(true, std::memory_order_relaxed);
    }

    bool isVisited() const {
        return visited.load(std::memory_order_relaxed);
    }

    void resetVisited() {
        visited.store(false, std::memory_order_relaxed);
    }


};

#endif //SRC_NODE_H
