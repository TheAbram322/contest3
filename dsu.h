#include <vector>
using std::vector;

struct Subtree
{
    Subtree(int parent, int rank) : parent(parent), rank(rank) {}
    int parent;
    int rank;
};

class DSU{

public:

    DSU(int v): numSubTrees(v), subtrees(v, Subtree(0,0)){
        for (int i = 0; i < v; ++i){
            subtrees[i].parent = i;
            subtrees[i].rank = 0;
        }
    }

    int findSubtree(int vertex);
    void unionSubtrees(int first, int second);
    int getNumOfSubtrees();
private:
    int numSubTrees;
    vector<Subtree> subtrees;

};






