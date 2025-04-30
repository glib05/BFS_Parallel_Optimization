//
// Created by User on 29.04.2025.
//

#ifndef SRC_BFS_H
#define SRC_BFS_H

#include <queue>
#include <unordered_map>
#include <optional>
#include <iostream>
#include "Node.h"

template <typename T>
class BFS {
public:
    using NodePtr = typename Node<T>::Ptr;

    std::optional<NodePtr> search(NodePtr root, const std::function<bool(const T&)>& goalChecker) {
        parentMap.clear();
        if (!root) return std::nullopt;

        std::queue<NodePtr> Q;
        root->markVisited();
        visitedQ.push(root);
        Q.push(root);

        while (!Q.empty()) {
            NodePtr v = Q.front();
            Q.pop();

            if (goalChecker(v->getData())) {
                resetVisited();
                return v;  // знайдено ціль
            }

            for (NodePtr w : v->getNeighbors()) {
                if (!w->isVisited()) {
                    w->markVisited();
                    visitedQ.push(w);
                    parentMap[w.get()] = v;  // для побудови шляху
                    Q.push(w);
                }
            }
        }

        resetVisited();
        return std::nullopt;  // не знайдено
    }

    void resetVisited(){
        while (!visitedQ.empty()) {
            NodePtr node = visitedQ.front();
            visitedQ.pop();
            node->resetVisited();
        }
    }

    // Відновити шлях до цілі (якщо знайдено)
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
    std::unordered_map<Node<T>*, NodePtr> parentMap;  // для відновлення шляху
    std::queue<NodePtr> visitedQ;
};

#endif //SRC_BFS_H
