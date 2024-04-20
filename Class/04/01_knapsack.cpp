#include <climits>
#include <stdio.h>
#include <vector>

using namespace std;

const int INF = INT_MAX;

int main(void) {
    int N;
    int V;

    scanf("%d %d", &N, &V);

    // values
    vector<int> w(N + 1, 0);
    // masses
    vector<int> v(N + 1, 0);


    for (int i = 1; i < N + 1; i++) {
        scanf("%d", &w[i]);
    }

    for (int i = 1; i < N + 1; i++) {
        scanf("%d", &v[i]);
    }
   
    vector<vector<int> > DP(N + 1, vector<int>(V + 1, -INF));
    DP[0][0] = 0;

    int max_value = -1;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= V; j++) {

            int value1 = -INF; 

            if (j - v[i] >= 0) {
                value1 = DP[i - 1][j - v[i]] + w[i];
            }

            DP[i][j] = max(value1, DP[i - 1][j]);
            max_value = max(max_value, DP[i][j]);
        }
    }

    printf("%d\n", max_value);
}
