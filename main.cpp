#include <limits>
#include "graph.h"
#include"stdio.h"

using std::vector;
using std::swap;
const int maxValue = std::numeric_limits<int>::max();

struct Subtree
{
    Subtree(int parent, int rank) : parent(parent), rank(rank) {}
    int parent;
    int rank;
};

int findSubtree(vector<Subtree>& subtrees, int vertex){
    if (subtrees[vertex].parent != vertex){
          subtrees[vertex].parent = findSubtree(subtrees, subtrees[vertex].parent);
    }
    return subtrees[vertex].parent;
}

void unionSubtrees(vector<Subtree>& subtrees, int first, int second){
    int firstRoot = findSubtree(subtrees, first);
    int secondRoot = findSubtree(subtrees, second);

    Subtree firstSubtree = subtrees[firstRoot];
    Subtree secondSubtree = subtrees[secondRoot];

    if (firstRoot != secondRoot){
            if (firstSubtree.rank < secondSubtree.rank){
                swap(firstRoot, secondRoot);
            }
            subtrees[secondRoot].parent = firstRoot;
            if (firstSubtree.rank == secondSubtree.rank){
                ++subtrees[firstRoot].rank;
            }
        }
}

long long weightMST(Graph& graph){
    int weight = 0;

    unsigned v = graph.getNumberOfVertices();
    unsigned e = graph.getNumberOfEdges();
    int numSubTrees = v;
    vector<Subtree> subtrees(v, Subtree(0,0));
    for (unsigned i = 0; i < v; ++i){
        subtrees[i].parent = i;
        subtrees[i].rank = 0;
    }
    vector<Edge*> cheapestEdge(v, new Edge(-1, -1, maxValue));

    while(numSubTrees > 1){

        for (Edge* edge : cheapestEdge){
            edge->weight = maxValue;
        }

        for (unsigned i = 0; i < e; ++i){
            Edge* edge = graph.getEdgeAtIndex(i);
            int firstSet = findSubtree(subtrees, edge->from);
            int secondSet = findSubtree(subtrees, edge->to);

            if (firstSet != secondSet){
                if (cheapestEdge[firstSet]->weight > edge->weight && !edge->used){
                    cheapestEdge[firstSet] = edge;
                }

                if (cheapestEdge[secondSet]->weight > edge->weight && !edge->used){
                    cheapestEdge[secondSet] = edge;
                }
            }
        }

        for (unsigned i = 0; i < v; ++i){
            if (cheapestEdge[i]->weight != maxValue){
                Edge* edge = cheapestEdge[i];
                int firstSet = findSubtree(subtrees, edge->to);
                int secondSet = findSubtree(subtrees, edge->from);

                if (firstSet != secondSet){
                    weight += edge->weight;
                    edge->used = true;
                    unionSubtrees(subtrees, firstSet, secondSet);
                    --numSubTrees;
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
