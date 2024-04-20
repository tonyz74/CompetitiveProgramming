#include <iostream>
#include <vector>
#include <map>
#include <deque>

using namespace std;

#define MAX_N 505

int ans[MAX_N];
int graph[MAX_N][MAX_N];
int prefs[MAX_N][MAX_N];

// void solve(int start) {
// }

int main(void) {
    int N; cin >> N;

    for (int i = 1; i <= N; i++) {
        int self_appeared = false;
        for (int j = 1; j <= N; j++) {
            cin >> prefs[i][j];

            if (!self_appeared) {
                graph[i][prefs[i][j]] = 1;
            }
            if (prefs[i][j] == i) {
                self_appeared = true;
            }
        }
    }

    for (int mid = 1; mid <= N; mid++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (graph[i][mid] == 1 && graph[mid][j] == 1) {
                    graph[i][j] = 1;
                }
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (graph[prefs[i][j]][i]) {
                printf("%d\n", prefs[i][j]);
                break;
            }
        }
    }
}