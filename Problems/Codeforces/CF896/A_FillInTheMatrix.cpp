#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

void solve() {
    int n, m; cin >> n >> m;

    if (m == 1) {
        printf("0\n");
        for (int i = 0; i < n; i++) {
            printf("0\n");
        }
        return;
    }

    // n rows, m columns
    vector<vector<int> > mat(n, vector<int>(m, -1));
    map<int, set<int> > rem;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rem[i].insert(j);
        }
    }

    int step = 0;
    for (int col = 0; col < m; col++) {
        for (int row = 0; row < step; row++) {
            mat[row][col] = step - row - 1;
            rem[row].erase(mat[row][col]);
        }
        step++;

        if (step > n) break;
    }

    for (int row = 0; row < step - 1; row++) {
        int first_found = 0;
        for (int col = 0; col < m; col++) {
            if (mat[row][col] != -1) {
                first_found = col;
                break;
            }
        } 

        for (int col = first_found - 1; col >= 0; col--) {
            int last = *rem[row].rbegin(); 
            mat[row][col] = last;
            rem[row].erase(last);
        }
    }

    // do whatever for the remaining ones
    for (int row = 0; row < step - 1; row++) {
        for (int col = 0; col < m; col++) {
            if (mat[row][col] != -1) continue;
            int any = *rem[row].begin();
            mat[row][col] = any;
            rem[row].erase(any);
        }
    }

    // copy the rows down
    for (int row = step - 1; row < n; row++) {
        for (int col = 0; col < m; col++) {
            mat[row][col] = mat[row - 1][col];
        }
    }

    printf("%d\n", step);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}