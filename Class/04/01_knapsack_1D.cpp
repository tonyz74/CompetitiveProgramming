#include <climits>
#include <stdio.h>
#include <vector>

using namespace std;

int main(void) {
    int N;
    int V;

    scanf("%d %d", &N, &V);

    // values
    vector<int> w(N + 1, 0);
    // masses
    vector<int> v(N + 1, 0);


    for (int i = 1; i < N; i++) {
        scanf("%d", &w[i]);
    }

    for (int i = 1; i < N; i++) {
        scanf("%d", &v[i]);
    }
   
    vector<int> DP(V + 1, 0);

    for (int i = 1; i <= N; i++) {
        for (int j = V; j >= 0; j--) {
            int value1 = 0; 

            if (j - v[i] >= 0) {
                value1 = DP[j - v[i]] + w[i];
            }

            DP[j] = max(value1, DP[j]);
        }
    }

    printf("%d\n", DP[V]);
}
