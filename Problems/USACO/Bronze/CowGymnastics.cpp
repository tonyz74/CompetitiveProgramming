#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main(void) {
    freopen("gymnastics.in", "r", stdin);
    freopen("gymnastics.out", "w", stdout);

    int K, N;
    cin >> K >> N;

    vector<vector<int> > data(K, vector<int>(N));
    
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            cin >> data[i][j];
            data[i][j]--;   // we're doing 0 indexed cows
        }
    }

    int cnt = 0;

    for (int c1 = 0; c1 < N; c1++) for (int c2 = 0; c2 < N; c2++) {
        // check if are a consistent pair
        bool all = true;
        for (int i = 0; i < K; i++) {
            auto idx_c1 = find(data[i].begin(), data[i].end(), c1) - data[i].begin();
            auto idx_c2 = find(data[i].begin(), data[i].end(), c2) - data[i].begin();

            if (idx_c1 <= idx_c2) {
                all = false;
                break;
            }
        }

        if (all) {
            // printf("cow %d and %d\n", c1 + 1, c2 + 1);
            cnt++;
        }
    }

    printf("%d\n", cnt);
}