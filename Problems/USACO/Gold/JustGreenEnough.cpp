#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

int N;
int grid_save[501][501];
int grid[501][501];

i64 calc_ans() {
    // fix top left point
    vector<vector<int> > nearest_rhs_zero(501, vector<int>(501, -1));

    for (int row = 1; row <= N; row++) {
        for (int i = 1; i <= N; i++) {
            int location = -1;
            for (int j = i; j <= N; j++) {
                if (grid[row][j] == 0) {
                    location = j;
                    break;
                }
            }
            
            if (location != -1) {
                nearest_rhs_zero[row][i] = location;
            }

            // printf("%3d ", nearest_rhs_zero[row][i]);
        }
        // printf("\n");
    }

    i64 ans = 0;

    // enumerate top left point
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            if (grid[row][col] == 0) continue;

            int min_rhs_zero = N + 1;

            for (int bottom_row = row; bottom_row <= N; bottom_row++) {
                if (nearest_rhs_zero[bottom_row][col] != -1) {
                    min_rhs_zero = min(min_rhs_zero, nearest_rhs_zero[bottom_row][col]);
                }
                ans += min_rhs_zero - col; 
            } 
        }
    }

    return ans;
}

int main(void) {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> grid_save[i][j];
            grid[i][j] = grid_save[i][j] >= 100;
        }
    }

    i64 gte_100 = calc_ans();
    // printf("%lld\n", gte_100);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            grid[i][j] = grid_save[i][j] > 100;
        }
    }

    i64 gt_100 = calc_ans();

    cout << (gte_100 - gt_100) << endl; 
}