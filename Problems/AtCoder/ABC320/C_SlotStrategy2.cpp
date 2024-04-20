#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int M;
    cin >> M;

    string S1, S2, S3;
    cin >> S1 >> S2 >> S3;

    int best = 3 * M + 1;
    for (int digit = '0'; digit <= '9'; digit++) {
        // pick the best way, then calculate time
        vector<int> ordering({1, 2, 3});
        auto cmp = [&] (int x, int y) { return ordering[x] < ordering[y]; };

        do {
            vector<bool> visited(3, false);

            int t = 0;
            while (t <= 3 * M + 1) {
                vector<int> v;
                if (S1[t % M] == digit && !visited[0]) v.push_back(0);
                if (S2[t % M] == digit && !visited[1]) v.push_back(1);
                if (S3[t % M] == digit && !visited[2]) v.push_back(2);

                sort(v.begin(), v.end(), cmp);
                
                if (v.size() != 0) {
                    visited[v[0]] = true;
                }

                if (visited[0] == true && visited[1] == true && visited[2] == true) {
                    break;
                }

                t++;
            }

            best = min(best, t);
        } while (next_permutation(ordering.begin(), ordering.end()));
    }

    if (best == 3 * M + 1) {
        printf("-1\n");
    } else {
        printf("%d\n", best);
    }
}