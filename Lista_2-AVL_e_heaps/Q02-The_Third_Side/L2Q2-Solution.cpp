#include <iostream>
#include <vector>

using namespace std;

int main() {
    int cases, n, num;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        cin >> n;
        int last = 0;
        for (int j = 0; j < n; j++) {
            cin >> num;
            last += num;
        }
        cout << last - n + 1 << endl;
    }

    return 0;
}