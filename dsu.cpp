#include "dsu.h"

using std::swap;

int DSU::findSubtree(int vertex){
    if (subtrees[vertex].parent != vertex){
          subtrees[vertex].parent = findSubtree(subtrees[vertex].parent);
    }
    return subtrees[vertex].parent;
}

void DSU::unionSubtrees(int first, int second){
    int firstRoot = findSubtree(first);
    int secondRoot = findSubtree(second);

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
    --numSubTrees;
}

int DSU::getNumOfSubtrees(){
    return numSubTrees;
}
