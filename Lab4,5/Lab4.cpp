#include "Graph.h"
#include "GreedyColorer.h"
#include "BeeSwarm.h"

int main()
{
    srand(time(NULL));
    Graph graph(20, 100);
    graph.generateRandGraph();
    BeeSwarm colorer(1000, 3, 27);
    graph = colorer.colourGraph(graph);
    cout << endl;
}
