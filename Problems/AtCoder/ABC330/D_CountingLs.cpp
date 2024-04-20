#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef long long ll;

int main(void) {
    int N; cin >> N;

    vector<string> board(N);
    vector<int> n_in_row(N, 0);
    vector<int> n_in_col(N, 0);

    for (int i = 0; i < N; i++) {
        string S; cin >> S;
        board[i] = S;

        for (int j = 0; j < N; j++) {
            if (S[j] == 'o') {
                n_in_row[i]++;
                n_in_col[j]++;
                // os.push_back(make_pair(i, j));
                // col_os[j].push_back(i);
                // row_os[i].push_back(j);
            }
        }
    }

    ll total = 0;

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            // fix the o at (row, col) in place
            if (board[row][col] != 'o') continue;
            total += (n_in_row[row] - 1)*(n_in_col[col] - 1);
        }
    }

    cout << total << endl;
}