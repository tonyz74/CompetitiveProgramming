#include <stdio.h>
#include <vector>

using namespace std;

int main(void) {
    int s;
    scanf("%d", &s);

    vector<int> weights(s + 1, 0);
    vector<int> values(s + 1, 0);

    for (int n = 1; n <= s; n++) {
        weights[n] = n; 
        for (int i = 1; i < n; i++) {
            if (n % i == 0) {
                values[n] += i;
            }
        } 
    }

    vector<int> dp(s + 1, 0);

    for (int i = 1; i <= s; i++) {
        for (int j = s; j >= 0; j--) {
            int other = 0;

            if (j - weights[i] >= 0) { 
                other = dp[j - weights[i]] + values[i];
            }

            dp[j] = max(dp[j], other);
        }
    } 

    printf("%d\n", dp[s]);
}
