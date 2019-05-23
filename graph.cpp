#include "graph.h"

unsigned Graph::getNumberOfVertices() const{
    return numberOfVertices;
}

unsigned Graph::getNumberOfEdges() const{
    return numberOfEdges;
}

Edge Graph::getEdgeAtIndex(int index) const{
    return edges[index];
}

void Graph::addEdge(int from, int to, int weight){
    edges.emplace_back(from, to, weight);
}
