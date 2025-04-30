//
// Created by User on 29.04.2025.
//

#ifndef SRC_GRAPH_H
#define SRC_GRAPH_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "Node.h"

struct AdjMatrix {
    std::vector<std::vector<bool>> matrix;

    static AdjMatrix readFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        size_t n;
        file >> n;

        AdjMatrix adj;
        adj.resize(n);

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                int value;
                if (!(file >> value)) {
                    throw std::runtime_error("Invalid matrix format in file.");
                }
                adj.matrix[i][j] = (value != 0);
            }
        }

        return adj;
    }

    void resize(size_t n) {
        matrix.resize(n);
        for (auto& row : matrix)
            row.resize(n, false);
    }

    void addEdge(size_t from, size_t to) {
        if (from >= matrix.size() || to >= matrix.size())
            throw std::out_of_range("Invalid index in addEdge");
        matrix[from][to] = true;
    }

    [[nodiscard]] bool hasEdge(size_t from, size_t to) const {
        if (from >= matrix.size() || to >= matrix.size())
            return false;
        return matrix[from][to];
    }

    void removeEdge(size_t from, size_t to) {
        if (from < matrix.size() && to < matrix.size())
            matrix[from][to] = false;
    }

    [[nodiscard]] size_t size() const {
        return matrix.size();
    }
};

template <typename T>
class Graph {
private:
    std::vector<typename Node<T>::Ptr> nodes;
    AdjMatrix adjMatrix;

public:
    using NodePtr = typename Node<T>::Ptr;

    Graph() = default;

    Graph(const AdjMatrix& matrix, const std::vector<T>& values) {
        size_t n = values.size();
        if (matrix.matrix.size() != n)
            throw std::invalid_argument("Matrix size must match number of node values.");
        adjMatrix = matrix;
        for (size_t i = 0; i < n; ++i) {
            nodes.push_back(std::make_shared<Node<T>>(values[i]));
        }
        for (size_t i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++){
                if (hasEdge(i,j))
                nodes[i]->addNeighbor(nodes[j]);
            }
        }

    }


    size_t addNode(const T& value) {
        NodePtr node = std::make_shared<Node<T>>(value);
        nodes.push_back(node);
        adjMatrix.resize(nodes.size());
        return nodes.size() - 1;
    }

    void addEdge(size_t from, size_t to) {
        if (from >= nodes.size() || to >= nodes.size())
            throw std::out_of_range("Invalid index in addEdge");

        adjMatrix.addEdge(from, to);
        nodes[from]->addNeighbor(nodes[to]);
    }

    NodePtr getNode(size_t index) const {
        if (index >= nodes.size())
            throw std::out_of_range("Invalid node index");
        return nodes[index];
    }

    [[nodiscard]] bool hasEdge(size_t from, size_t to) const {
        return adjMatrix.hasEdge(from, to);
    }

    [[nodiscard]] size_t size() const {
        return nodes.size();
    }

    void print() const {
        for (size_t i = 0; i < size(); ++i) {
            std::cout << "Node " << i << " (" << nodes[i]->getData() << ") -> ";
            auto neighbors = nodes[i]->getNeighbors();
            for (const auto& neighbor : neighbors) {
                std::cout << neighbor->getData() << " ";
            }
            std::cout << "\n";
        }
    }
};


#endif //SRC_GRAPH_H
