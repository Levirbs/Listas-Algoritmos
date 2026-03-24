#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

struct Edge {
    int u, v, weight;
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

struct UnionFind {
    vector<int> parent;
    UnionFind(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int curr) {
        if (parent[curr] == curr) return curr;
        parent[curr] = find(parent[curr]);
        return parent[curr];
    }
    void unite(int a, int b) {
        int root1 = find(a);
        int root2 = find(b);
        if (root1 != root2) parent[root2] = root1;
    }
};

long long kruskal (int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compareEdges);

    UnionFind dsu(n);
    int maxW = 0;
    int edges_in_mst = 0;

    for (auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            maxW = max(maxW, edge.weight);
            edges_in_mst++;
        }
    }

    if (edges_in_mst < n - 1) return -1;
    return maxW;
}

int main() {
    int n, m, a, b, w;
    while (true) {
        cin >> n >> m;
        if (n == 0 && n == m) break;
        vector<Edge> edges;
        for (int i = 0; i < m; i++) {
            cin >> a >> b >> w;
            edges.push_back({a, b, w});
        }

        long long mst_cost = kruskal(n, edges);

        if (mst_cost == -1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << mst_cost << endl;
        }
    }

    return 0;
}