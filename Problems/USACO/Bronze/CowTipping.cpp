#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N;
vector<string> state;

bool is_all_zeroes() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (state[i][j] != '0') return false;
        }
    }
    return true;
}

void flip(pair<int, int> endpoint) {
    for (int i = 0; i <= endpoint.first; i++) {
        for (int j = 0; j <= endpoint.second; j++) {
            if (state[i][j] == '0') state[i][j] = '1';
            else state[i][j] = '0';
        }
    }

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) printf("%c", state[i][j]);
    //     printf("\n");
    // }
}

int main(void) {
    freopen("cowtip.in", "r", stdin);
    freopen("cowtip.out", "w", stdout);

    cin >> N;
    state.resize(N);

    for (int i = 0; i < N; i++) {
        cin >> state[i];
    }

    int n_ops = 0;

    while (!is_all_zeroes()) {
        // find the rightmost rectangle, flip that, then find the 
        // bottommost rectangle, and also flip that

        // row, column
        pair<int, int> rightmost = {-1, -1};
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) if (state[i][j] == '1') {
            if (j > rightmost.second) {
                rightmost = make_pair(i, j);
            } else if (j == rightmost.second && i > rightmost.first) {
                rightmost = make_pair(i, j);
            }
        }

        flip(rightmost);
        n_ops++;

        if (is_all_zeroes()) break;
        pair<int, int> bottommost = {-1, -1};
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) if (state[i][j] == '1') {
            if (i > bottommost.first) {
                bottommost = make_pair(i, j);
            } else if (i == bottommost.first && j > bottommost.second) {
                bottommost = make_pair(i, j);
            }
        }

        flip(bottommost);
        n_ops++;
    }

    cout << n_ops << endl;
}