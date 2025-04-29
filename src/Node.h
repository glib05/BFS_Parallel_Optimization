//
// Created by User on 29.04.2025.
//

#ifndef SRC_NODE_H
#define SRC_NODE_H

#include <vector>

using namespace std;

template <typename T>
class Node {
private:
    T value_;
    vector<Node<T>> neighbors_;
    bool visited_ = false;

public:
    void visit(){
        visited_ = true;
    }
    void unvisit(){
        visited_ = false;
    }

    bool visited() const{
        return visited_;
    }

public:
    explicit Node(const T& value, vector<Node<int>> &neighbors) : value_(value), neighbors_(neighbors) {}
    explicit Node(const T& value) : value_(value){}
    Node(const Node<T>& other){
        this->value_ = other.value_;
        this->neighbors_ = other.neighbors_;
        this->visited_ = other.visited_;
    }
    Node& operator=(const Node<T>& other){
        this->value_ = other.value_;
        this->neighbors_ = other.neighbors_;
        this->visited_ = other.visited_;
        return *this;
    }

    T& operator*() {
        return value_;
    }

    const T& operator*() const {
        return value_;
    }

    vector<Node<T>> &getNeighbors(){
        return neighbors_;
    }

    void addNeighbor(const Node<T> &neighbor){
        neighbors_.push_back(neighbor);
    }

    void addNeighborMutually(Node<T> &neighbor){
        this->addNeighbor(neighbor);
        neighbor.addNeighbor(*this);
    }

    int neighborCount() const {
        return neighbors_.size();
    }


};

#endif //SRC_NODE_H
