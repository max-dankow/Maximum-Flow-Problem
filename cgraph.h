#ifndef CGRAPH_H
#define CGRAPH_H

#include <stdlib.h>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iostream>

struct CEdge
{
    CEdge(size_t newFirstVertex, size_t newSecondVertex, double newWeight, double newCapacity, double newFlow):
        firstVertexIndex(newFirstVertex), secondVertexIndex(newSecondVertex),
        weight(newWeight), capacity(newCapacity), flow(newFlow){}
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
    CGraph(size_t newVerticesAmount);
    void addEdge(const CEdge &newEdge);
    CEdge getEdge(size_t firstVertexIndex, size_t secondVertexIndex, CEdge &result) const;
private:
    size_t verticesAmount;
    std::vector<std::vector<CEdge> > edgesList;
    void depthFirstSearch(size_t vertexIndex, std::vector<bool> &visited, std::vector<size_t> &way);
};

#endif // CGRAPH_H
