#include <vector>

using std::vector;

struct Edge{
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight), used(false){}
    int from;
    int to;
    int weight;
    bool used;
};

class Graph{
public:
    Graph(unsigned n, unsigned m): numberOfVertices(n), numberOfEdges(m){}
    unsigned getNumberOfVertices() const;
    unsigned getNumberOfEdges() const;
    Edge* getEdgeAtIndex(int index);
    void addEdge(int from, int to, int weight);

private:
    vector<Edge> edges;
    unsigned numberOfVertices;
    unsigned numberOfEdges;
};

