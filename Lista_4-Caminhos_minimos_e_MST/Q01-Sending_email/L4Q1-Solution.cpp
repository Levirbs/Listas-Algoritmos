#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
 
using namespace std;
 
#define int long long int
 
const int INF = 1e16;
 
int first (vector<vector<int>>& graph, int v, int n) {
    for (int i = 0; i < n; i++) {
        if (graph[v][i] != 0) return i;
    }
    return n;
}
 
int next (vector<vector<int>>& graph, int v, int w, int n) {
    for (int i = w + 1; i < n; i++) {
        if (graph[v][i] != 0) return i;
    }
    return n;
}
 
void Dijkstra(vector<vector<tuple<int, int>>>& graph, int s, int n, vector<int>& D) {
    priority_queue<pair<int, int>> H;
    vector<bool> visited(n, false);
    D.assign(n, INF);
    H.push({0, s});
    D[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        do {
            if (H.empty()) {
                v = -1;
                break;
            }
            v = H.top().second;
            H.pop();
        } while (v != -1 && visited[v]);
        if (v == -1) break;
        visited[v] = true;
 
        for(auto [next, custo] : graph[v]) {
            if (!visited[next] && D[next] > D[v] + custo) {
                D[next] = D[v] + custo;
                H.push({-D[next], next});
        }
        }
    }
}
 
signed main() {
    int N, n, m, S, T, a, b, w;
    cin >> N;
    vector<int> distances;
    for (int i = 0; i < N; i++) {
        cin >> n >> m >> S >> T;
        vector<vector<tuple<int, int>>> graph(n);
        for (int j = 0; j < m; j++) {
            cin >> a >> b >> w;
            graph[a].push_back({b, w});
            graph[b].push_back({a, w});
        }

        Dijkstra(graph, S, n, distances);

        cout << "Case #" << i + 1<< ": ";
        if (distances[T] == INF) {
            cout << "unreachable" << endl;
        } else {
            cout << distances[T] << endl;
        }
    }

    return 0;
}
