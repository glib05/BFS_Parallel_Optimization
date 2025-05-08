//
// Created by User on 02.05.2025.
//

#ifndef MAIN_CPP_PARALLELBFS_H
#define MAIN_CPP_PARALLELBFS_H


#include <thread>
#include <atomic>
#include <vector>
#include <optional>
#include <unordered_map>
#include "Node.h"
#include "BockingQueue.h"

template <typename T>
class ParallelBFS {
public:
    using NodePtr = typename Node<T>::Ptr;

    std::optional<NodePtr> search(NodePtr root, const std::function<bool(const T&)>& goalChecker, int threadCount) {
        if (!root) return std::nullopt;

        reset();  // очищення стану

        root->markVisited();
        visitedQ.push(root);
        taskQueue.push(root);

        std::atomic<bool> found = false;
        std::optional<NodePtr> result;
        std::mutex resultMtx;

        std::vector<std::thread> workers;

        for (int i = 0; i < threadCount; ++i) {
            workers.emplace_back([&]() {
                NodePtr current;

                while (!found && taskQueue.pop(current)) {
                    if (goalChecker(current->getData())) {
                        std::lock_guard<std::mutex> lock(resultMtx);
                        found = true;
                        result = current;
                        break;
                    }

                    for (NodePtr neighbor : current->getNeighbors()) {
                        std::lock_guard<std::mutex> lock(visitMtx);
                        if (!neighbor->isVisited()) {
                            neighbor->markVisited();
                            visitedQ.push(neighbor);
                            parentMap[neighbor.get()] = current;
                            taskQueue.push(neighbor);
                        }
                    }
                }
            });
        }

        for (auto& t : workers) t.join();

        resetVisited();
        return result;
    }

    std::vector<NodePtr> reconstructPath(NodePtr goal) const {
        std::vector<NodePtr> path;
        while (goal) {
            path.push_back(goal);
            auto it = parentMap.find(goal.get());
            if (it != parentMap.end()) {
                goal = it->second;
            } else {
                break;
            }
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

private:
    std::unordered_map<Node<T>*, NodePtr> parentMap;
    std::queue<NodePtr> visitedQ;
    BlockingQueue<NodePtr> taskQueue;
    std::mutex visitMtx;

    void reset() {
        parentMap.clear();
        std::queue<NodePtr> empty;
        std::swap(visitedQ, empty);
        // taskQueue не очищується вручну, бо одразу додається root
    }

    void resetVisited() {
        while (!visitedQ.empty()) {
            NodePtr node = visitedQ.front();
            visitedQ.pop();
            node->resetVisited();
        }
    }
};

#endif //MAIN_CPP_PARALLELBFS_H
