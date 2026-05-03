#include <iostream>
#include "Graph.h"
#include "Algorithms.h"
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int dirFlag, wFlag;

    cout << "Enter n: ";
    cin >> n;
    cout << "Directed? (0/1): ";
    cin >> dirFlag;
    cout << "Weighted? (0/1): ";
    cin >> wFlag;

    cout << "Enter m: ";
    cin >> m;

    Graph g(n, m, dirFlag==1, wFlag==1);

    cout << "Enter edges u v w (if unweighted, w ignored and treated as 1):\n";
    for(int i=0;i<m;i++){
        int u,v; long long w;
        cin >> u >> v >> w;
        g.addEdge(i, u, v, w);
    }

    while(true){
        cout << "\n===== Menu =====\n";
        cout << "1) Print adjacency list\n";
        cout << "2) Print adjacency matrix\n";
        cout << "3) DFS traversal\n";
        cout << "4) BFS traversal\n";
        cout << "5) Connected components\n";
        cout << "6) Kruskal MST\n";
        cout << "7) Dijkstra shortest paths\n";
        cout << "0) Exit\n";
        cout << "Choose: ";

        int op;
        cin >> op;
        if(!cin || op==0) break;

        if(op==1) g.printAdjList();
        else if(op==2) g.printAdjMatrix();
        else if(op==3){ int s; cout << "Start: "; cin >> s; DFS(g, s); }
        else if(op==4){ int s; cout << "Start: "; cin >> s; BFS(g, s); }
        else if(op==5){ ConnectedComponents(g); }
        else if(op==6){ Kruskal(g); }
        else if(op==7){ int s; cout << "Source: "; cin >> s; Dijkstra(g, s); }
        else cout << "Unknown option.\n";
    }

    return 0;
}
