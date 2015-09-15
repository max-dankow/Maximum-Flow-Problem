#ifndef CNETWORK_H
#define CNETWORK_H
#include "cgraph.h"

class CNetwork
{
public:
    CGraph graph;
    CNetwork(size_t newVerticesAmount, size_t newSource, size_t newSink):
        graph(CGraph(newVerticesAmount)), sourceVertex(newSource), sinkVertex(newSink){}
    void algorithmEdmondsKarp();
    double getFlowAmount();
private:
    size_t sourceVertex, sinkVertex;
};

#endif // CNETWORK_H
