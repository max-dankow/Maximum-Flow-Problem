#include "cnetwork.h"

CNetwork readInput()
{
    size_t verticesAmount, egdesAmount;
    std::cin >> verticesAmount >> egdesAmount;
    CNetwork inputNetwork(verticesAmount, 0, verticesAmount - 1);
    for (size_t i = 0; i < egdesAmount; ++i)
    {
        size_t firstVertex, secondVertex;
        double capacity;
        std::cin >> firstVertex >> secondVertex >> capacity;
        inputNetwork.addEdge(CEdge(firstVertex - 1, secondVertex - 1, 1, capacity, 0));
    }
    return inputNetwork;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    CNetwork network = readInput();
    network.algorithmEdmondsKarp();
    std::cout << network.getFlowAmount() << '\n';
    return 0;
}
