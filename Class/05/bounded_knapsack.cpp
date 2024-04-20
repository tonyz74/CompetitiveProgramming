#include <vector>
#include <stdio.h>

using namespace std;

int main(void) {
    int N, V;

    scanf("%d %d", &N, &V);

    vector<int> weights(N + 1, 0), values(N + 1, 0), counts(N + 1, 0);
    vector<int> new_weights(1, 0), new_values(1, 0);

    // input format:
    // weight[i], value[i], count[i]

    for (int i = 1; i <= N; i++) {
        scanf("%d %d %d", &weights[i], &values[i], &counts[i]);
    }

    for (int i = 1; i <= N; i++) {
        // counts
        int subtotal = counts[i];

        int tp = 0;
        int pow = 1 << tp;
        while (subtotal - pow >= 0) {
            subtotal -= pow;

            // add to the new weights and new values
            int new_wt = weights[i] * pow;
            int new_val = values[i] * pow;
            new_weights.push_back(new_wt);
            new_values.push_back(new_val);

            tp++;
            pow = 1 << tp;
        }

        if (subtotal != 0) {
            // got some stuff remaining
            new_weights.push_back(weights[i] * subtotal);
            new_values.push_back(values[i] * subtotal);
        }
    }
    

    vector<int> DP(V + 1, 0);

    N = new_weights.size();

    for (int i = 1; i <= N; i++) {
        for (int j = V; j >= 0; j--) {
            if (j - new_weights[i] >= 0) {
                DP[j] = max(DP[j - new_weights[i]] + new_values[i], DP[j]);
            }
        }
    }

    printf("%d\n", DP[V]);
}
