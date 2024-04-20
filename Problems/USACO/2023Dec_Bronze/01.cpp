#include <iostream>
#include <vector>
#include <set>

typedef long long i64;

using namespace std;

int main(void) {
    // brute force first
    i64 N, M;
    cin >> N >> M;
    vector<i64> heights(N);
    vector<i64> canes(M);

    for (int i = 0; i < N; i++) cin >> heights[i];
    for (int i = 0; i < M; i++) cin >> canes[i];

    for (int cane = 0; cane < M; cane++) {
        i64 cane_left = canes[cane];
        i64 dist_from_ground = 0;

        for (int cow = 0; cow < N; cow++) {
            if (cane_left == 0) break;

            if (heights[cow] > dist_from_ground) {
                i64 can_eat = heights[cow] - dist_from_ground;
                i64 actual_eaten = min(can_eat, cane_left);

                cane_left -= actual_eaten;
                heights[cow] += actual_eaten;
                dist_from_ground += actual_eaten;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        cout << heights[i] << endl;
    }
}