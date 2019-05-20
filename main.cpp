#include "graph.h"
#include <iostream>



using std::vector;
using std::cout;


int main() {
    unsigned n, m;
    scanf("%d", &n);
    scanf("%d", &m);

    Graph graph(n);

    for (unsigned i = 0; i < m; i++) {
        int from, to, capacity;

        scanf("%d", &from);
        scanf("%d", &to);
        scanf("%d", &capacity);

        graph.addEdge(from - 1, to - 1, capacity);
    }

    cout << graph.maxFlow(0, n - 1);
}
