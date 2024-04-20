#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N; cin >> N;
    vector<vector<int> > adj(N + 1, vector<int>(N + 1, 0));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> adj[i][j];
        }
    }

    for (int start = 1; start <= N; start++) {
        for (int x = 1; x <= N; x++) {
            if (adj[start][x] != 0) {
                printf("%d ", x);
            }
        }
        printf("\n");
    }

}