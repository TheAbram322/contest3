#include <vector>

using std::vector;

struct Edge{
    Edge(int from, int to, int capacity): from(from), to(to), capacity(capacity), usedCapacity(0){}
    int from;
    int to;
    int capacity;
    int usedCapacity;
};

class Graph {

public:
    Graph(int n): numberOfVertices(n), numbersOfEdges(n), used(n, false), relatedEdge(n) {}

    void addEdge(int from, int to, int capacity);

    long long maxFlow(int from, int to);

private:
    unsigned numberOfVertices;
    vector<Edge> edges;
    vector<vector<int> > numbersOfEdges;
    vector<bool> used;
    vector<int> relatedEdge;

    void BFS(int vertex);

    bool hasWay(int from, int to);
    int minCapacityOnWay(int from, int to);
    void addToFlow(int from, int to, int flow);
};
