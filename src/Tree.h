//
// Created by User on 29.04.2025.
//

#ifndef SRC_TREE_H
#define SRC_TREE_H

#include "Node.h"

template <typename T>
class Tree{
    Node<T> root_;
public:
    Tree() = default;

    explicit Tree(const T& rootValue) {
        root_ = Node<T>(rootValue);
    }

    explicit Tree(const Node<T>& root) {
        root_ = root;
    }

    Node<T> getRoot() const {
        return root_;
    }

    void setRoot(const Node<T>& root) {
        root_ = root;
    }

    void addChild(const Node<T>& parent, const T& childValue) {
        Node<T> child = Node<T>(childValue);
        addChild();
    }

    void addChild(const Node<T>& parent, const Node<T>& child){
        parent.addNeighbor(child);
    }
};

#endif //SRC_TREE_H
