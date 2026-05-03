#include <iostream>
#include "LinkedGraph.h"
#include "WeightedGraph.h"
using namespace std;
int main() {
    cout << "=== LinkedGraph ===\n";
    LinkedGraph lg(5);
    lg.insertEdge(0, 3);
    lg.insertEdge(0, 4);
    lg.insertEdge(1, 2);
    lg.insertEdge(1, 3);

    lg.display();
    lg.DFS(0);
    lg.BFS(0);
    lg.ConnectedComponents();

    cout << "\n=== WeightedGraph ===\n";
    WeightedGraph wg(4);
    wg.insertEdge(0, 1, 12);
    wg.insertEdge(0, 2, 7);
    wg.insertEdge(0, 3, 9);
    wg.insertEdge(1, 3, 14);
    wg.insertEdge(2, 3, 3);

    wg.display();
    cout << endl;
    wg.Prim(0);
    cout << endl;
    wg.Kruskal();
    cout << endl;
    wg.Dijkstra(0);

    return 0;
}
