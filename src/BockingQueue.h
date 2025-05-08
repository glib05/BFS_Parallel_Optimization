//
// Created by User on 02.05.2025.
//

#ifndef MAIN_CPP_BOCKINGQUEUE_H
#define MAIN_CPP_BOCKINGQUEUE_H


#include <mutex>
#include <condition_variable>
#include <queue>

template<typename T>
class BlockingQueue {
private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void push(const T& value) {
        std::unique_lock<std::mutex> lock(mtx);
        queue.push(value);
        cv.notify_one();
    }

    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !queue.empty(); });
        value = queue.front();
        queue.pop();
        return true;
    }

    bool empty() {
        std::unique_lock<std::mutex> lock(mtx);
        return queue.empty();
    }
};


#endif //MAIN_CPP_BOCKINGQUEUE_H
