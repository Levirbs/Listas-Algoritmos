#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long int // so testar se o wrong answer foi por causa de overflow

// notei, novamente, que a logica desse problema é muito similar ao knapsack problem apresentado nos slides
// vou adaptar a logica apresentada pelo pseudocodigo para se encaixar neste problema
int knapsackModified(int n, int m, int c_insert, int c_delete, int c_modify, string s, string t) {
    vector<vector<int>> F(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 && j == 0) {
                F[i][j] = 0;

            } else if (i == 0) {
                F[i][j] = j * c_insert;

            } else if (j == 0) {
                F[i][j] = i * c_delete;
                
            } else {
                int c1 = F[i - 1][j] + c_delete;
                
                int c2 = F[i][j - 1] + c_insert;

                int c3;
                if (s[i - 1] == t[j - 1]) {
                    c3 = F[i - 1][j - 1];
                } else {
                    c3 = F[i - 1][j - 1] + c_modify;
                }

                F[i][j] = min({c1, c2, c3});
            }
        }
    }
    return F[n][m];
}

signed main() {
    int n, m, a, b, c;
    string s, t;

    cin >> n >> m >> a >> b >> c >> s >> t;

    cout << knapsackModified(n, m, a, b, c, s, t) << endl;

    return 0;
}