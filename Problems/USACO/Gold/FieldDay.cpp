#include <iostream>
#include <vector>
#include <climits>
#include <deque>

using namespace std;

int main(void) {
    int C, N; cin >> C >> N;

    vector<int> teams(N);
    for (int i = 0; i < N; i++) {
        string T; cin >> T;
        int mask = 0;
        for (int j = 0; j < C; j++) {
            if (T[j] == 'G') mask |= (1 << j);
        }

        teams[i] = mask;
    }

    vector<int> min_dist(1 << C, -1);
    deque<int> current; 

    for (int i = 0; i < N; i++) {
        current.push_back(teams[i]);
        min_dist[teams[i]] = 0;
    }

    while (!current.empty()) {
        int front = current.front();
        current.pop_front();

        for (int edit = 0; edit < C; edit++) {
            int new_mask = front ^ (1 << edit);

            if (min_dist[new_mask] == -1) {
                min_dist[new_mask] = min_dist[front] + 1;
                current.push_back(new_mask);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        int inv = 0;
        for (int j = 0; j < C; j++) {
            if ((teams[i] & (1 << j)) == 0) {
                inv |= (1 << j);
            }
        }

        printf("%d\n", C - min_dist[inv]);
    }
}