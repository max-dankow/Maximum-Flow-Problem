#include "cnetwork.h"

void CNetwork::algorithmEdmondsKarp()
{
  //обнулить поток
    for (auto it = edgesList.begin(); it != edgesList.end(); ++it)
    {
        for (auto edgesIt = it->begin(); edgesIt != it->end(); ++edgesIt)
        {
            edgesIt->flow = 0;
        }
    }
    while(true)
    {
      //находим кратчайший путь в остаточной сети
        std::vector<bool> visited(verticesAmount, false);
        std::vector<ssize_t> ancestors(verticesAmount, NO_ANCESTOR);
        breadthFirstSearch(sourceVertex, visited, ancestors);
      //восстановить путь ведущий в sink, если NO_ANCESTOR, то закончить
        if (ancestors[sinkVertex] == NO_ANCESTOR)
        {
            break;
        }
        size_t currentVertex = sinkVertex;
      //находим ребро в остаточной сети с минимальной остаточной пропускной способностью
        std::vector<CEdge>::iterator currentEdge;
        getEdge(ancestors[sinkVertex], sinkVertex, currentEdge);
        double minCapacityOnWay = currentEdge->capacity;
        while(currentVertex != sourceVertex)
        {
            getEdge(ancestors[currentVertex], currentVertex, currentEdge);
            if (currentEdge->capacity < minCapacityOnWay)
            {
                minCapacityOnWay = currentEdge->capacity;
            }
            currentVertex = ancestors[currentVertex];
        }
      //перебираем все ребра и обратные ребра на пути и изменяем flow и capacity
        currentVertex = sinkVertex;
        while(currentVertex != sourceVertex)
        {
          //обновляем прямые ребра пути
            getEdge(ancestors[currentVertex], currentVertex, currentEdge);
            currentEdge->capacity -= minCapacityOnWay;
            currentEdge->flow += minCapacityOnWay;
          //удаляем обнулившиеся ребра из остаточной сети
            if (currentEdge->capacity <= 0)
            {
                currentEdge->weight = std::numeric_limits<double>::infinity();
            }
          //обновляем обратные ребра пути, если они есть
            if (getEdge(currentVertex, ancestors[currentVertex], currentEdge))
            {
                currentEdge->capacity += minCapacityOnWay;
                currentEdge->flow -= minCapacityOnWay;
              //удаляем обнулившиеся ребра из остаточной сети
                if (currentEdge->capacity <= 0)
                {
                    currentEdge->weight = std::numeric_limits<double>::infinity();
                }
            }
            currentVertex = ancestors[currentVertex];
        }
    }
}

double CNetwork::getFlowAmount() const
{
    double flowSum = 0;
    for (CEdge edge : edgesList[sourceVertex])
    {
        flowSum += edge.flow;
    }
    return flowSum;
}

