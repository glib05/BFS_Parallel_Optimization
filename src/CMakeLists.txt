cmake_minimum_required(VERSION 3.23)
project(src)

set(CMAKE_CXX_STANDARD 23)

add_executable(src main.cpp Node.h NodeStructure.h Graph.h Tree.h BFS.h ParallelBFS.h BockingQueue.h ThreadPool.h)
