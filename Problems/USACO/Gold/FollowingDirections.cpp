#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define int long long

int N, Q;
int grid[3200][3200];
int n_reaching[3200][3200];

void traverse(int row, int col, int val_change) {
    while (row != N && col != N) {
        n_reaching[row][col] += val_change;
        
        if (grid[row][col] == 'D') {
            row += 1;
        } else {
            col += 1;
        }
    }

    n_reaching[row][col] += val_change;
}

long long find_total() {
    long long tot = 0;
    for (int i = 0; i < N; i++) {
        tot += (long long) n_reaching[i][N] * (long long) grid[i][N];
        tot += (long long) n_reaching[N][i] * (long long) grid[N][i];
    }

    return tot;
}

signed main(void) {
    cin >> N;

    for (int i = 0; i < N; i++) {
        string S; cin >> S;
        for (int j = 0; j < N; j++) {
            grid[i][j] = (int) S[j];
        }
        int cost; cin >> cost;
        grid[i][N] = cost;
    }

    for (int j = 0; j < N; j++) {
        int cost;
        cin >> cost;
        grid[N][j] = cost;
    }

    for (int row = 0; row < N; row++) for (int col = 0; col < N; col++) n_reaching[row][col] = 1;

    for (int row = 0; row <= N; row++) {
        for (int col = 0; col <= N; col++) {
            if (row == col && row == N) continue;

            int from_left = 0; 

            // PAY ATTENTION: DON'T TRANSITION FROM AN INTEGER!!!!!

            if (col != 0 && row != N && grid[row][col - 1] == (int) 'R') {
                from_left += n_reaching[row][col - 1];
            }

            int from_above = 0;
            if (row != 0 && col != N && grid[row - 1][col] == (int) 'D') {
                from_above += n_reaching[row - 1][col];
            }

            n_reaching[row][col] += (from_left + from_above);
        }
    }

    // for (int row = 0; row <= N; row++){
    //     for (int col = 0; col <= N; col++) {
    //         printf("%d ", n_reaching[row][col]);
    //     }
    //     printf("\n");

    // }

    cout << find_total() << endl;
 
    cin >> Q;

    for (int q = 0; q < Q; q++) {
        int row, col; cin >> row >> col;
        row--; col--;

        int x = n_reaching[row][col];
        traverse(row, col, -x);

        if (grid[row][col] == 'D') grid[row][col] = 'R';
        else grid[row][col] = 'D';

        traverse(row, col, x);

        cout << find_total() << endl;
    }
}