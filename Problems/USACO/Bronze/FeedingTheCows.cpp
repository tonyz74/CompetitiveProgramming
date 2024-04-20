#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve() {
    int N, K; cin >> N >> K;
    string S; cin >> S;

    string output(N, '.');

    int nearest_G = -1;
    int nearest_H = -1;

    int shift = 0;

    for (int i = 0; i < N; i++) {
        if (S[i] == 'G') {
            bool should_place = false;
            if (nearest_G == -1) should_place = true;
            else {
                int dist = abs(i - nearest_G);
                // printf("[%d] dist = %d, nearest G: %d\n", i, dist, nearest_G);
                if (dist > K) should_place = true;
            }

            if (should_place) {
                int ind = min(N - 1, i + K);
                if (ind == N - 1) {
                    shift++;
                    ind -= (shift - 1);
                }

                output[ind] = 'G';
                nearest_G = ind;
            }
        } else {
            bool should_place = false;
            if (nearest_H == -1) should_place = true;
            else {
                int dist = abs(i - nearest_H);
                // printf("[%d] dist = %d, nearest H: %d\n", i, dist, nearest_H);
                if (dist > K) should_place = true;
            }

            if (should_place) {
                int ind = min(N - 1, i + K);
                if (ind == N - 1) {
                    shift++;
                    ind -= (shift - 1);
                }

                output[ind] = 'H';
                nearest_H = ind;
            }
        }
    }

    int x = 0;
    for (char c: output) {
        if (c != '.') x++;
    }

    cout << x << endl;
    cout << output << endl;
}

int main(void) {
    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) solve();
}