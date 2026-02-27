#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> parent, depth;

public:
    DisjointSet(int n) {
        parent.resize(n);
        depth.assign(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findSet(int x) {
        if (parent[x] != x)
            parent[x] = findSet(parent[x]);
        return parent[x];
    }

    void mergeSets(int a, int b) {
        a = findSet(a);
        b = findSet(b);

        if (a == b) return;

        if (depth[a] < depth[b])
            parent[a] = b;
        else if (depth[b] < depth[a])
            parent[b] = a;
        else {
            parent[b] = a;
            depth[a]++;
        }
    }
};

int findMSTCost(int vertices, vector<vector<int>> &edges) {

    sort(edges.begin(), edges.end(),
         [](const vector<int> &x, const vector<int> &y) {
             return x[2] < y[2];
         });

    DisjointSet ds(vertices);
    int mstCost = 0;

    for (auto &e : edges) {
        int u = e[0];
        int v = e[1];
        int w = e[2];

        if (ds.findSet(u) != ds.findSet(v)) {
            mstCost += w;
            ds.mergeSets(u, v);
        }
    }

    return mstCost;
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