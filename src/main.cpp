#include <iostream>
#include <numeric>
#include "BFS.h"
#include "Graph.h"
#include "ParallelBFS.h"

int main() {

    const int SIZE = 1000;

    using NodePtr = BFS<int>::NodePtr;

    std::vector<int> numbers(SIZE);  // Розмір вектора 50
    std::iota(numbers.begin(), numbers.end(), 0);
    Graph g = Graph<int>(AdjMatrix::readFromFile(R"(D:\KPI\6_semestr\TPO\BFS_Parallel_Optimization\src\1000matrix.txt)"),
                         numbers);

//    BFS bfs = BFS<int>();
    ParallelBFS bfs = ParallelBFS<int>();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
//            auto result = bfs.search(g.getNode(i), [&j](const int &val) { return val == j; });
            auto result = bfs.search(g.getNode(76), [&j](const int& val) { return val == 345; }, 10);

            if (result) {
                std::cout << "Found node: " << (*result)->getData() << "\n";
                auto path = bfs.reconstructPath(*result);
                std::cout << "Path: ";
                for (auto &node: path) {
                    std::cout << node->getData() << " ";
                }
                std::cout << "\n";
            } else {
//                std::cout << "Goal not found.\n";
            }
        }
    }
//    result = bfs.search(n1, [](const int& val) { return val == 4; });
//
//    if (result) {
//        std::cout << "Found node: " << (*result)->getData() << "\n";
//        auto path = bfs.reconstructPath(*result);
//        std::cout << "Path: ";
//        for (auto& node : path) {
//            std::cout << node->getData() << " ";
//        }
//        std::cout << "\n";
//    } else {
//        std::cout << "Goal not found.\n";
//    }

    return 0;
}
