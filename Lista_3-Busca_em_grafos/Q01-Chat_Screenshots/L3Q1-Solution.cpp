#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

#define UNVISITED 0
#define VISITED_1 1
#define VISITED_2 2

using namespace std;

void toposort_check(int u, vector<vector<int>>& graph, vector<int>& mark, bool& contradiction, stack<int>& s) {
    if (contradiction) {
        return;
    }
    mark[u] = VISITED_1;
    for (int v : graph[u]) {
        if (mark[v] == UNVISITED) {
            toposort_check(v, graph, mark, contradiction, s);
        }

        else if (mark[v] == VISITED_1) { //contradicao
            contradiction = true;
            return;
        }
    }
    mark[u] = VISITED_2;
    s.push(u);
}

int main () {
    int t, n, k;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n >> k;
        vector<int> mark(n + 1, UNVISITED);
        stack<int> s;
        vector<vector<int>> graph(n + 1);
        for (int j = 0; j < k; j++) {
            vector<int> screenshot(n);
            for (int l = 0; l < n; l++) {
                cin >> screenshot[l];
            }

            for (int l = 1; l < n - 1; l++) {
                int a = screenshot[l];
                int b = screenshot[l + 1];
                graph[a].push_back(b);
            }
        }
        
        bool contradiction = false;
        for (int j = 1; j <= n; j++) {
            if(mark[j] == UNVISITED) {
                toposort_check(j, graph, mark, contradiction, s);
            }

        }
        if (!contradiction) {
             cout << "YES";
            } else {
            cout << "NO";
        }
        cout << endl;
    }
    return 0;
}