#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;

i64 paint[1024][1024];

int main(void) {
    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);

    i64 N; cin >> N;
    i64 K; cin >> K;

    for (i64 i = 0; i < N; i++) {
        i64 start_x, start_y, end_x, end_y;
        cin >> start_x >> start_y >> end_x >> end_y;
        paint[start_y][start_x]++;
        paint[start_y][end_x]--;

        paint[end_y][start_x]--;
        paint[end_y][end_x]++;
    }

    i64 total = 0;

    for (i64 i = 0; i <= 1010; i++) {
        for (i64 j = 0; j <= 1010; j++) {
            if (j >= 1) paint[i][j] += paint[i][j - 1];
            if (i >= 1) paint[i][j] += paint[i - 1][j];
            if (i >= 1 && j >= 1) paint[i][j] -= paint[i - 1][j - 1];

            if (paint[i][j] == K) total++;
            // printf("%lld ", paint[i][j]);
        }
        // printf("\n");
    }

    cout << total << endl;
}