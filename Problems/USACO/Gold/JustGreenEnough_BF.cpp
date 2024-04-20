#include <iostream>
#include <vector>

using namespace std;

int N;
int grid[501][501];

int main(void) {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> grid[i][j];
        }
    }

    int ans = 0;

    for (int r1 = 1; r1 <= N; r1++) {
        for (int c1 = 1; c1 <= N; c1++) {
            for (int r2 = r1; r2 <= N; r2++) {
                for (int c2 = c1; c2 <= N; c2++) {

                    int min_inside = 1e9;
                    for (int i = r1; i <= r2; i++) {
                        for (int j = c1; j <= c2; j++) {
                            min_inside = min(min_inside, grid[i][j]);
                        }
                    }

                    if (min_inside == 100) {
                        ans++;
                    }

                }
            }
        }
    }

    printf("%d\n", ans);
}