#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

int main(void) {
    int n;
    scanf("%d", &n);

    vector<int> numbers(n + 1, 0);
    for (int i = 1; i < n + 1; i++) {
        int x;
        scanf("%d", &x);
        numbers[i] = x;
    }


    vector<int> sums(n + 1, 0);
    vector<int> DP(n + 1, 0);

    // precalculate sums
    for (int i = 1; i < n + 1; i++) {
        sums[i] = sums[i - 1] + numbers[i]; 
    }
    

    double eps = 1e-6;
    const int INF = 1e9;

    for (int i = 1; i < n + 1; i++) {
        int max_val = -1;

        for (int j = 0; j < i; j++) {
            int sum = sums[i] - sums[j];
            int sqr = (int) sqrt(sum);

            if (fabs((float) sqr - (float) sqrt(sum)) < eps) {
                // is perfect square
                if (DP[j] == -1) {
                    continue;
                }

                int candidate = DP[j] + 1;
                max_val = max(max_val, candidate);
            }
        }

        DP[i] = max_val;
    }

    printf("%d\n", DP[n]);
}
