#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

// notei que esse problema é muito similar ao change-making problem apresentado nos slides (slide 8)
// vou adaptar a logica apresentada pelo pseudocodigo para se encaixar neste problema

int ChangeMakingModified(vector<int>& coins, int n, int x) {
    vector<int> F(x + 1, INF);
    F[0] = 0;
    
    for (int i = 1; i <= x; i++) {
        int temp = INF;
        int j = 0;
        
        while (j < n && i >= coins[j]) {
            if (F[i - coins[j]] != INF) temp = min(F[i - coins[j]] + 1, temp);
            j++;
        }
        F[i] = temp;
    }
    
    if (F[x] == INF) return -1;
    return F[x];
}

int main() {
    int n, x, coin;
    cin >> n >> x;

    vector<int> coins(n);
    for (int i = 0; i < n; ++i) {
        cin >> coin;
        coins[i] = coin;
    }

    sort(coins.begin(), coins.end()); // tem que ordenar para ter garantia que todas as moedas seguintes sao iguais ou maiores

    cout << ChangeMakingModified(coins, n, x) << endl;

    return 0;
}