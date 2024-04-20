#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 201

struct cow {
    int x, y;
    int power;
};

int N;
vector<cow> cows;
int graph[MAX_N][MAX_N];

bool can_reach(int i, int j) {
    int x_off = (cows[i].x - cows[j].x);
    int y_off = (cows[i].y - cows[j].y);
    int dist_sq = x_off * x_off + y_off * y_off;
    return dist_sq <= cows[i].power * cows[i].power;
}

int main(void) {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    cin >> N;
    cows.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> cows[i].x >> cows[i].y >> cows[i].power;
    }

    for (int start = 1; start <= N; start++) {
        for (int other = 1; other <= N; other++) {
            if (can_reach(start, other)) {
                // printf("%d can reach %d\n", start, other);
                graph[start][other] = 1;
            }
        }
    }

    // for (int i = 1; i <= N; i++) {
    //     for (int j = 1; j <= N; j++) {
    //         printf("%d ", graph[i][j]);
    //     }
    //     printf("\n");
    // }

    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (graph[i][k] && graph[k][j]) {
                    graph[i][j] = 1;
                }
            }
        }
    }

    // printf("after floyd\n");

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        int ones = 0;
        for (int j = 1; j <= N; j++) {
            ones += graph[i][j];
            // printf("%d ", graph[i][j]);
        }
        ans = max(ans, ones);
        // printf("\n");
    }
    printf("%d\n", ans);
}
