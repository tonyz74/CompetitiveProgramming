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


    for (int i = 1; i <= N; i++) {
        scanf("%d", &w[i]);
    }

    for (int i = 1; i <= N; i++) {
        scanf("%d", &v[i]);
    }
   
    vector<vector<int> > DP(N + 1, vector<int>(V + 1, 0));

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= V; j++) {
            int value1 = 0; 

            if (j - v[i] >= 0) {
                value1 = DP[i - 1][j - v[i]] + w[i];
            }

            DP[i][j] = max(value1, DP[i - 1][j]);
        }
    }

    printf("%d\n", DP[N][V]);
}
