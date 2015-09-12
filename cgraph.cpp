#include "cgraph.h"

CGraph::CGraph(size_t newVerticesAmount): verticesAmount(newVerticesAmount)
{
    edgesList.assign(verticesAmount, std::vector<CEdge>());
}

void CGraph::addEdge(const CEdge &newEdge)
{
    assert(newEdge.firstVertexIndex < verticesAmount && newEdge.secondVertexIndex < verticesAmount);
    edgesList[newEdge.firstVertexIndex].push_back(newEdge);
}

void CGraph::addEdgeUndirected(const CEdge &newEdge)
{
    addEdge(newEdge);
    addEdge(CEdge(newEdge.secondVertexIndex, newEdge.firstVertexIndex, newEdge.weight));
}

void CGraph::depthFirstSearch(size_t vertexIndex, std::vector<bool> &visited, std::vector<size_t> &way)
{
    assert(vertexIndex < verticesAmount);
    visited[vertexIndex] = true;
    way.push_back(vertexIndex);
    for (size_t i = 0; i < edgesList[vertexIndex].size(); ++i)
    {
        size_t nextVertexIndex = edgesList[vertexIndex][i].secondVertexIndex;
        if (!visited[nextVertexIndex])
        {
            depthFirstSearch(nextVertexIndex, visited, way);
        }
    }
}

std::vector<size_t> CGraph::rebuildWay()
{
    std::vector<bool> visited(verticesAmount, false);
    std::vector<size_t> way;
    depthFirstSearch(0, visited, way);
    way.push_back(0);
    return way;
}
