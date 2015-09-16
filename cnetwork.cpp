#include "cnetwork.h"

void CNetwork::algorithmEdmondsKarp()
{
  //обнулить поток
    for (auto it = graph.edgesList.begin(); it != graph.edgesList.end(); ++it)
    {
        for (auto edgesIt = it->begin(); edgesIt != it->end(); ++edgesIt)
        {
            edgesIt->flow = 0;
        }
    }
    while(true)
    {
      //находим кратчайший путь в остаточной сети
        std::vector<bool> visited(graph.verticesAmount, false);
        std::vector<ssize_t> ancestors(graph.verticesAmount, graph.NO_ANCESTOR);
        graph.breadthFirstSearch(sourceVertex, visited, ancestors);
      //восстановить путь ведущий в sink, если NO_ANCESTOR, то закончить
        if (ancestors[sinkVertex] == graph.NO_ANCESTOR)
        {
            break;
        }
        size_t currentVertex = sinkVertex;
      //находим ребро в остаточной сети с минимальной остаточной пропускной способностью
        std::vector<CEdge>::iterator currentEdge;
        graph.getEdge(ancestors[sinkVertex], sinkVertex, currentEdge);
        double minCapacityOnWay = currentEdge->capacity;
        while(currentVertex != sourceVertex)
        {
            graph.getEdge(ancestors[currentVertex], currentVertex, currentEdge);
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
            graph.getEdge(ancestors[currentVertex], currentVertex, currentEdge);
            currentEdge->capacity -= minCapacityOnWay;
            currentEdge->flow += minCapacityOnWay;
          //удаляем обнулившиеся ребра из остаточной сети
            if (currentEdge->capacity <= 0)
            {
                currentEdge->weight = std::numeric_limits<double>::infinity();
            }
          //обновляем обратные ребра пути, если они есть
            if (graph.getEdge(currentVertex, ancestors[currentVertex], currentEdge))
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
    for (CEdge edge : graph.edgesList[sourceVertex])
    {
        flowSum += edge.flow;
    }
    return flowSum;
}

