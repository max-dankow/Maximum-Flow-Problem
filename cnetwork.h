#ifndef CNETWORK_H
#define CNETWORK_H
#include "cgraph.h"

class CNetwork : public CGraph
{
public:
    CNetwork(size_t newVerticesAmount, size_t newSource, size_t newSink):
        CGraph(newVerticesAmount), sourceVertex(newSource), sinkVertex(newSink){}
    void algorithmEdmondsKarp();
    double getFlowAmount() const;
private:
    size_t sourceVertex, sinkVertex;
};

#endif // CNETWORK_H
