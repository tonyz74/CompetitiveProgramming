#include <stdio.h>
#include <vector>

using namespace std;

int main(void) {
    int count, money;
    scanf("%d %d", &money, &count);

    // v -> prices, w -> ratings
    vector<int> prices(count + 1, 0), ratings(count + 1, 0);
    vector<int> true_vals(count + 1, 0);

    for (int i = 1; i < count + 1; i++) {
        scanf("%d %d", &prices[i], &ratings[i]);
        true_vals[i] = prices[i] * ratings[i];
    }

    vector<vector<int> > DP(count + 1, vector<int>(money + 1, 0));

    for (int i = 1; i < count + 1; i++) {
        for (int j = 0; j < money + 1; j++) {
            int val1 = 0;
            
            if (j - prices[i] >= 0) {
                val1 = DP[i - 1][j - prices[i]] + true_vals[i];
            }

            DP[i][j] = max(val1, DP[i - 1][j]);
        }
    }

    printf("%d\n", DP[count][money]);
}
