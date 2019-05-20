#include "graph.h"
#include <queue>
#include <limits>

using std::queue;
const int maxValue = std::numeric_limits<int>::max();
using std::min;

void Graph::addEdge(int from, int to, int capacity) {
    edges.emplace_back(from, to, capacity);
    int number = edges.size() - 1;
    numbersOfEdges[from].emplace_back(number);
    numbersOfEdges[to].emplace_back(number);
}

long long Graph::maxFlow(int from, int to) {
    long long sizeOfMaxFlow = 0;
    while (hasWay(from, to)){
        int sizeOfCurrentFlow = minCapacityOnWay(from, to);
        addToFlow(from, to, sizeOfCurrentFlow);
        sizeOfMaxFlow += sizeOfCurrentFlow;
    }
    return sizeOfMaxFlow;
}


void Graph::BFS(int vertex) {
    queue<int> q;
    used[vertex] = true;
    q.push(vertex);
    while (!q.empty()) {
        vertex = q.front();
        q.pop();
        for (unsigned i = 0; i < numbersOfEdges[vertex].size(); ++i) {
            int e = numbersOfEdges[vertex][i];
            Edge edge = edges[e];
            int to;
            int currentCapacity;
            if (vertex == edge.from){
                to = edge.to;
                currentCapacity = edge.capacity - edge.usedCapacity;
            } else {
                to = edge.from;
                currentCapacity = edge.usedCapacity;
            }

            if (!used[to] && currentCapacity != 0) {
                relatedEdge[to] = e;
                used[to] = true;
                q.push(to);
            }
        }
    }
}

bool Graph::hasWay(int from, int to) {

    used.assign(numberOfVertices, false);
    BFS(from);

    return used[to];
}

int Graph::minCapacityOnWay(int from, int to) {
    int minCapacity = maxValue;
    int vertex = to;
    while (vertex != from){
        int currentCapacity;

        Edge edge = edges[relatedEdge[vertex]];

        if (vertex == edge.from){
            vertex = edge.to;
            currentCapacity = edge.usedCapacity;
        } else {
            vertex = edge.from;
            currentCapacity = edge.capacity - edge.usedCapacity;
        }

        minCapacity = min(minCapacity, currentCapacity);

    }

    return minCapacity;
}

void Graph::addToFlow(int from, int to, int flow) {
    int vertex = to;
    while (vertex != from){
        Edge* edge = &edges[relatedEdge[vertex]];
        if (vertex == edge->from){
            edges[relatedEdge[vertex]].usedCapacity -= flow;
        } else {
            edges[relatedEdge[vertex]].usedCapacity += flow;
        }

        if (vertex == edge->from){
            vertex = edge->to;
        } else {
            vertex = edge->from;
        }
    }
}
