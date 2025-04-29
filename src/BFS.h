//
// Created by User on 29.04.2025.
//

#ifndef SRC_BFS_H
#define SRC_BFS_H

#include "Node.h"
#include <queue>
#include <any>

template <typename T>
class BFS{
public:
    vector<Node<T>> visited_;
public:
    Node<T>& search(Node<T> &start, const T &goal){
        queue<Node<T>> q_;
        visited_.clear();
        q_.push(start);
        bool found = false;
        visited_.push_back(start);
        start.visit();
        Node<T> &current = start;
        while (!q_.empty()){
            current = q_.front();
            q_.pop();
            if (*current == goal){
//                return current;
                break;
                found = true;
            }
            for (auto &neighbor : current.getNeighbors()){
                if (!neighbor.visited()){
                    neighbor.visit();
                    visited_.push_back(neighbor);
                    q_.push(neighbor);
                }
            }
        }
        for (auto v: visited_){
            v.unvisit();
        }
        if (!found){
            current = Node<T>(-999);
        }
        return current;

    }
};

#endif //SRC_BFS_H
