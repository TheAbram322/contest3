#include <limits>
#include "graph.h"
#include"stdio.h"
#include <dsu.h>

using std::vector;
using std::swap;
const int maxValue = std::numeric_limits<int>::max();



long long weightMST(const Graph& graph){
    int weight = 0;

    unsigned v = graph.getNumberOfVertices();
    unsigned e = graph.getNumberOfEdges();
    DSU dsu(v);

    vector<Edge> cheapestEdge(v, Edge(-1, -1, maxValue));

    while(dsu.getNumOfSubtrees() > 1){

        for (unsigned i = 0; i < v; ++i){
            cheapestEdge[i].weight = maxValue;
        }

        for (unsigned i = 0; i < e; ++i){
            Edge edge = graph.getEdgeAtIndex(i);
            int firstSet = dsu.findSubtree(edge.from);
            int secondSet = dsu.findSubtree(edge.to);

            if (firstSet != secondSet){
                if (cheapestEdge[firstSet].weight > edge.weight && !edge.used){
                    cheapestEdge[firstSet] = edge;
                }

                if (cheapestEdge[secondSet].weight > edge.weight && !edge.used){
                    cheapestEdge[secondSet] = edge;
                }
            }
        }

        for (unsigned i = 0; i < v; ++i){
            if (cheapestEdge[i].weight != maxValue){
                Edge edge = cheapestEdge[i];
                int firstSet = dsu.findSubtree(edge.to);
                int secondSet = dsu.findSubtree(edge.from);

                if (firstSet != secondSet){
                    weight += edge.weight;
                    cheapestEdge[i].used = true;
                    dsu.unionSubtrees(firstSet, secondSet);
                }
            }
        }
    }
    return weight;
}

int main(){
    unsigned n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    Graph graph(n, m);
    for (size_t i = 0; i < m; ++i){
        int from, to, weight;
        scanf("%d", &from);
        scanf("%d", &to);
        scanf("%d", &weight);

        graph.addEdge(from - 1, to - 1, weight);
    }

    printf("%lld", weightMST(graph));
    return 0;
}
