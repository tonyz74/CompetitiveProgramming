#include <iostream>
#include <vector>

using namespace std;

int N;
int beauty[1024][1024];

int main(void) {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> beauty[i][j];
        }
    }

    // place in columns
    int col_ans = 0;
    for (int col = 1; col <= N; col++) {
        int best_for_current = 0;

        for (int off = 0; off <= 1; off++) {
            int off_sum = 0;
            for (int row = off; row <= N; row += 2) {
                off_sum += beauty[row][col];
            }

            best_for_current = max(best_for_current, off_sum);
        }

        col_ans += best_for_current;
    }

    // place in rows
    int row_ans = 0;
    for (int row = 1; row <= N; row++) {
        int best_for_current = 0;

        for (int off = 0; off <= 1; off++) {
            int off_sum = 0;
            for (int col = off; col <= N; col += 2) {
                off_sum += beauty[row][col];
            }

            best_for_current = max(best_for_current, off_sum);
        }

        row_ans += best_for_current;
    }

    // print final answer
    printf("%d\n", max(row_ans, col_ans));
}