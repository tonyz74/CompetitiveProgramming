#include <iostream>
#include <vector>

using namespace std;

bool reserved[9][9];
bool state[9][9];
int N_ways = 0;

bool used_cols[9];
bool downright[1024];
bool upright[1024];

// currently placing a queen on this row
void search(int row) {
    if (row == 9) {
        N_ways++;
        return;
    }

    for (int col = 1; col <= 8; col++) {
        int dr_id = 8 + (col - row);
        int ur_id = row + col;

        if (reserved[row][col]) continue;
        if (used_cols[col] || downright[dr_id] || upright[ur_id]) continue;

        // try with this one set
        used_cols[col] = true;
        downright[dr_id] = true;
        upright[ur_id] = true;

        search(row + 1);

        used_cols[col] = false;
        downright[dr_id] = false;
        upright[ur_id] = false;
    }
}

int main(void) {
    for (int i = 0; i < 8; i++) {
        string S; cin >> S;
        for (int j = 0; j < 8; j++) {
            if (S[j] == '*') reserved[i + 1][j + 1] = true;
        }
    }

    search(1);
    cout << N_ways << endl;
}