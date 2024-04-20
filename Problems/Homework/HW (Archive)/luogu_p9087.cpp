#include <stdio.h>
#include <vector>

using namespace std;

void solve(int n, int k, int a, int b) {
    int len = n;
    int cover_len = 2 * k - 2;
    int slices_in_cover = k - 1;
    int current_index = 0;

    vector<int> splits;
    int current_cost = (n - k) * b;

    if (n < k) {
        printf("0\n");
        for (int i = 0; i < n; i++) {
            printf("%d", i % 2);
        }
        return;
    }

    while (len > 1) {
        int other = max(len - k + 1, 0); 
        // printf("other = %d, current = %d\n", other, current_cost);
        int alt_cost = current_cost + a - (min(slices_in_cover, other) * b);

        // make the change
        if (alt_cost <= current_cost) {
            current_cost = alt_cost;
            int translation = min(slices_in_cover, len - 1);
            splits.push_back(current_index + translation - 1); 
            splits.push_back(current_index + translation); 
            // printf("translation = %d, i = %d\n", translation, current_index);

            if (len < cover_len) {
                break;
            }

            len -= translation;
            current_index += translation;
        } else {
            break;
        }
    }

    printf("%ld\n", (splits.size() / 2) * a);
    int i = 0;
    for (int k = 0; k < n; k++) {
        if (i < splits.size() && splits[i] == k) {
            printf("a");
            i++;
        } else {
            printf("%d", k % 2);
        }
    }
    printf("\n");
}

int main(void) {
    int T;
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        int n, k, a, b;
        scanf("%d %d %d %d", &n, &k, &a, &b);
        solve(n, k, a, b);
    }
}
