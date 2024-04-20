#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

char final_grid[1000][1000];
string initial_grid[20];

void setIO() {
    freopen("cowsignal.in", "r", stdin);
    freopen("cowsignal.out", "w", stdout);
}

int main(void) {
    setIO();
    
    int N, M, K; cin >> N >> M >> K;
    for (int row = 0; row < N; row++) {
        string s; cin >> s;
        initial_grid[row] = s;
    }

    for (int row = 0; row < N; row++) for (int col = 0; col < M; col++) {
        for (int rk = 0; rk < K; rk++) for (int ck = 0; ck < K; ck++) {
            final_grid[row * K + rk][col * K + ck] = initial_grid[row][col];
        }
    }

    for (int i = 0; i < N * K; i++) {
        for (int j = 0; j < M * K; j++)
            cout << final_grid[i][j];
        cout << endl;
    }
}
