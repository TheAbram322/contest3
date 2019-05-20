#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "graph.h"

using std::max;
using std::cout;





int main() {
    unsigned n, m;
    scanf("%d", &n);
    scanf("%d", &m);

    Graph graph(n + m + 2);

    vector<int> amountOfTea(m);

    int totalAmountOfTea = 0;

    for (unsigned i = 0; i < m; ++i){
        int amount;
        scanf("%d", &amount);
        totalAmountOfTea += amount;
        amountOfTea[i] = amount;
    }

    for (unsigned i = 0; i < n; ++i){
        graph.addEdge(0, i + 1, 0);
    }

    for (unsigned i = 0; i < n; ++i){
        unsigned amountOfSorts;
        scanf("%d", &amountOfSorts);
        for (unsigned j = 0; j < amountOfSorts; ++j){
            int numberOfSort;
            scanf("%d", &numberOfSort);
            graph.addEdge(i + 1, n + numberOfSort, amountOfTea[numberOfSort - 1]);
        }
    }

    for(unsigned i = 0; i < m; ++i){
        graph.addEdge(n + 1 + i, n + m + 1, amountOfTea[i]);
    }

    vector<int> values;

    int middle = 0;
    if (totalAmountOfTea >= (int)n){
        int left = 0;
        int right = totalAmountOfTea;
        while(left < right)
        {
          middle = (left + right + 1) / 2;
          graph.setPearsonsCapacity(n, middle);
          int flow = graph.maxFlow(0, n + m + 1);
          if (flow == (int)(n * middle)){
              values.push_back(middle);
          }
          if((right - left) == 1){
              break;
          }
          if (flow >= (int)(n * middle)){
              left = middle;
          } else {
              right = middle;
          }
        }
    } else {
        printf("0");
        return 0;
    }

    int maxValue = -1;
    unsigned size = values.size();
    for (unsigned i = 0; i < size; ++i){
        maxValue = max(maxValue, values[i]);
    }

    printf("%d", maxValue);
    return 0;
}
