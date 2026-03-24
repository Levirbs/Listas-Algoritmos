#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>

#define UNVISITED 0
#define VISITED 1

using namespace std;

vector<int> reconstruct_path(int start, int end, int n, vector<vector<int>>& graph) {
    vector<int> parent(n, -1);
    queue<int> q;

    q.push(start);
    
    bool found = false;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == end) {
            found = true;
            break;
        }
        sort(graph[u].begin(), graph[u].end());
        for (int v : graph[u]) {
            if (parent[v] == -1 && v != start) {
                parent[v] = u;
                q.push(v);
            }
        }
    }

    vector<int> path;
    if (found) {
        int curr = end;
        while(curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
    }
    return path;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n * m);
    vector<string> map(n);
    vector<vector<bool>> danger(n, vector<bool>(m, false));
    vector<int> path;

    for (int i = 0; i < n; i++) {
        cin >> map[i];
    }

    // making danger zones

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] != '.') { 
                danger[i][j] = true; 
                
                if (map[i][j] == '>') {
                    for (int k = j + 1; k < m; k++) {
                        if (map[i][k] != '.') {
                            break;
                        }
                        danger[i][k] = true;
                    }
                } else if (map[i][j] == 'v') {
                    for (int k = i + 1; k < n; k++) {
                        if (map[k][j] != '.') {
                            break;
                        }
                        danger[k][j] = true;
                    }
                } else if (map[i][j] == '<') {
                    for (int k = j - 1; k >= 0; k--) {
                        if (map[i][k] != '.') {
                            break;
                        }
                        danger[i][k] = true;
                    }                    
                } else { // ^
                    for (int k = i - 1; k >= 0; k--) {
                        if (map[k][j] != '.') {
                            break;
                        }
                        danger[k][j] = true;
                    }
                }
            }
        }
    }
    
    // making the graph

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!danger[i][j]) {
                int a = i * m + j;
                // direita
                if (j < m - 1 && !danger[i][j + 1]) {
                    graph[a].push_back(i * m + (j + 1));
                }

                // baixo
                if (i < n - 1 && !danger[i + 1][j]) {
                    graph[a].push_back((i + 1) * m + j);
                }
                
                // esquerda
                if (j > 0 && !danger[i][j - 1]) {
                    graph[a].push_back(i * m + (j - 1));
                }

                // cima
                if (i > 0 && !danger[i - 1][j]) {
                    graph[a].push_back((i - 1) * m + j);
                }
            }
        }
    }
    
    // output

    if (danger[n - 1][m - 1] == true || danger[0][0] == true) {
        cout << -1 << endl;

    } else {
        path = reconstruct_path(0, ((n - 1) * m + (m - 1)), n * m, graph);

        if (!path.empty()) {
            for (int p : path) {
                map[p / m][p % m] = 'X';
            }

            for (int i = 0; i < n; ++i) {
                cout << map[i] << endl;
            }
                
        } else {
            cout << -1 << endl;
        }
    }

    return 0;
}