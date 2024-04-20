#include <stdio.h>
#include <vector>

using namespace std;

int main(void) {
    int V, n;
    scanf("%d %d", &V, &n);

    vector<int> wt(n + 1, 0); 
    vector<int> vals(n + 1, 0);

    for (int i = 1; i < n + 1; i++) {
        scanf("%d", &wt[i]);

        // since we're finding the minimum remaining
        // weight, i'll just have every value equal
        // their weight, so maximizing value means
        // maximizing weight.
        vals[i] = wt[i];
    }


    // DP[i][j] = max(
    //     DP[i - 1][j - wt[i]] + val[i],
    //     ^ put this current item into sack
    //
    //     DP[i - 1][j]
    //     ^ skip this item
    // );

    vector<vector<int> > DP(n + 1, vector<int>(V + 1, 0));

    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < V + 1; j++) {
            int value1 = 0;

            if (j - wt[i] >= 0) {
                value1 = DP[i - 1][j - wt[i]] + vals[i];
            }

            DP[i][j] = max(value1, DP[i - 1][j]);
        }
    }

    printf("%d\n", V - DP[n][V]);
}
