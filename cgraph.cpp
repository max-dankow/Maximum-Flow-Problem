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

void CGraph::depthFirstSearch(size_t vertexIndex, std::vector<bool> &visited, std::vector<size_t> &way) const
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

bool CGraph::getEdge(size_t firstVertexIndex, size_t secondVertexIndex, std::vector<CEdge>::iterator& result)
{
    assert(firstVertexIndex < verticesAmount && secondVertexIndex < verticesAmount);
    CEdge edgeToFind(firstVertexIndex, secondVertexIndex, 0, 0, 0);
    std::vector<CEdge>::iterator searchResultIt = find(edgesList[firstVertexIndex].begin(), edgesList[firstVertexIndex].end(), edgeToFind);
    if (searchResultIt != edgesList[firstVertexIndex].end())
    {
        result = searchResultIt;
    }
    return searchResultIt != edgesList[firstVertexIndex].end();
}


void CGraph::breadthFirstSearch(size_t startVertexIndex, std::vector<bool> &visited, std::vector<ssize_t> &ancestors)
{
    std::queue<size_t> verticesQueue;
    verticesQueue.push(startVertexIndex);
    visited[startVertexIndex] = true;

    while(!verticesQueue.empty())
    {
        size_t currentVertex = verticesQueue.front();
        verticesQueue.pop();
        for (auto it = edgesList[currentVertex].begin(); it != edgesList[currentVertex].end(); ++it)
        {
            if (!visited[it->secondVertexIndex] && it->weight != std::numeric_limits<double>::infinity())
            {
                visited[it->secondVertexIndex] = true;
                ancestors[it->secondVertexIndex] = currentVertex;
                verticesQueue.push(it->secondVertexIndex);
            }
        }
    }
}
