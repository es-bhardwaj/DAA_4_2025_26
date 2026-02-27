#include <bits/stdc++.h>
using namespace std;

int findMSTCost(int vertices, vector<vector<int>> &edgeList) {

    vector<vector<pair<int,int>>> graph(vertices);

    for (auto &e : edgeList) {
        int from = e[0];
        int to   = e[1];
        int cost = e[2];

        graph[from].push_back({cost, to});
        graph[to].push_back({cost, from});
    }

    vector<bool> inMST(vertices, false);

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > minHeap;

    minHeap.push({0, 0});
    int totalCost = 0;

    while (!minHeap.empty()) {
        auto top = minHeap.top();
        minHeap.pop();

        int weight = top.first;
        int node   = top.second;

        if (inMST[node])
            continue;

        inMST[node] = true;
        totalCost += weight;

        for (auto &nbr : graph[node]) {
            if (!inMST[nbr.second]) {
                minHeap.push({nbr.first, nbr.second});
            }
        }
    }

    return totalCost;
}

int main() {

    int V = 5;

    vector<vector<int>> edges = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    cout << "Minimum Cost of MST: "
         << findMSTCost(V, edges) << endl;

    return 0;
}