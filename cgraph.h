#ifndef CGRAPH_H
#define CGRAPH_H

#include <stdlib.h>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <limits>

struct CEdge
{
    CEdge(size_t newFirstVertex, size_t newSecondVertex, double newWeight, double newCapacity, double newFlow):
        firstVertexIndex(newFirstVertex), secondVertexIndex(newSecondVertex),
        weight(newWeight), capacity(newCapacity), flow(newFlow){}
    CEdge(){}
    bool operator <(const CEdge &other) const
    {
        return weight < other.weight;
    }
    bool operator ==(const CEdge &other) const
    {
        return (firstVertexIndex == other.firstVertexIndex) &&
               (secondVertexIndex == other.secondVertexIndex);
    }
    size_t firstVertexIndex, secondVertexIndex;
    double weight, capacity, flow;
};

class CGraph
{
public:
    const int NO_ANCESTOR = -1;
    CGraph(size_t newVerticesAmount);
    void depthFirstSearch(size_t vertexIndex, std::vector<bool> &visited, std::vector<size_t> &way) const;
    void breadthFirstSearch(size_t startVertexIndex, std::vector<bool> &visited, std::vector<ssize_t> &ancestors);
    void addEdge(const CEdge &newEdge);
protected:
    size_t verticesAmount;
    std::vector<std::vector<CEdge> > edgesList;
    bool getEdge(size_t firstVertexIndex, size_t secondVertexIndex, std::vector<CEdge>::iterator& result);
};

#endif // CGRAPH_H
