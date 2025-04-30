#include <iostream>
#include <numeric>
#include "BFS.h"
#include "Graph.h"

int main() {

    using NodePtr = BFS<int>::NodePtr;

    std::vector<int> numbers(50);  // Розмір вектора 50
    std::iota(numbers.begin(), numbers.end(), 0);
    Graph g = Graph<int>(AdjMatrix::readFromFile(R"(D:\KPI\6_semestr\TPO\BFS_Parallel_Optimization\src\matrix1.txt)"),
                         numbers);

    BFS bfs = BFS<int>();

    auto result = bfs.search(g.getNode(47), [](const int& val) { return val == 2; });

    if (result) {
        std::cout << "Found node: " << (*result)->getData() << "\n";
        auto path = bfs.reconstructPath(*result);
        std::cout << "Path: ";
        for (auto& node : path) {
            std::cout << node->getData() << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "Goal not found.\n";
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
