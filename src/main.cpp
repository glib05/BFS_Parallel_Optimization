#include <iostream>
#include "BFS.h"

int main() {
    vector<Node<int>> v;
    for (int i = 0; i < 10; i++){
        v.emplace_back(i);
    }

    v[0].addNeighborMutually(v[1]);
    v[0].addNeighborMutually(v[2]);
    v[1].addNeighborMutually(v[2]);
    v[2].addNeighborMutually(v[0]);
    v[3].addNeighborMutually(v[1]);
    v[3].addNeighborMutually(v[9]);
    v[4].addNeighborMutually(v[5]);
    v[4].addNeighborMutually(v[0]);
    v[4].addNeighborMutually(v[9]);
    v[6].addNeighborMutually(v[5]);
    v[7].addNeighborMutually(v[1]);
    v[8].addNeighborMutually(v[2]);
    v[9].addNeighborMutually(v[2]);
    v[2].addNeighborMutually(v[4]);
    v[3].addNeighborMutually(v[9]);
    v[3].addNeighborMutually(v[5]);
    v[4].addNeighborMutually(v[2]);
    v[4].addNeighborMutually(v[8]);
    v[4].addNeighborMutually(v[7]);
    v[6].addNeighborMutually(v[2]);

    BFS<int> bfs;
    auto node = bfs.search(v[0], 1);

    cout<<*node;


    return 0;
}
