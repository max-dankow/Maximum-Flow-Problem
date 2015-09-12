#ifndef CGRAPH_H
#define CGRAPH_H

#include <stdlib.h>
#include <vector>
#include <assert.h>
#include <iostream>

struct CEdge
{
    CEdge(size_t newFirstVertex, size_t newSecondVertex, double newWeight):
        firstVertexIndex(newFirstVertex),secondVertexIndex(newSecondVertex), weight(newWeight){}
    bool operator <(const CEdge &other) const
    {
        return weight < other.weight;
    }
    size_t firstVertexIndex, secondVertexIndex;
    double weight;
};

class CGraph
{
public:
    CGraph(size_t newVerticesAmount);
    void addEdgeUndirected(const CEdge &newEdge);
    void addEdge(const CEdge &newEdge);
    std::vector<size_t> rebuildWay();
private:
    size_t verticesAmount;
    std::vector<std::vector<CEdge> > edgesList;
    void depthFirstSearch(size_t vertexIndex, std::vector<bool> &visited, std::vector<size_t> &way);
};

#endif // CGRAPH_H
