#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int stack[10000 + 5];
int a[10000 + 5];

int main(void) {
    int N; cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];

    // DP[i] -> longest for element ending at i
    vector<int> DP(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        int best = 0;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) best = max(best, DP[j]);
        }
        
        DP[i] = best + 1;
    }

    for (int i = 0; i <= N; i++)
        cout << DP[i] << endl;
}