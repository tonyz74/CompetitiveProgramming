#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);

    int N; cin >> N;
    vector<int> R(N + 1);
    for (int i = 1; i <= N; i++) cin >> R[i];

    int min_total = 1e9;
    for (int open = 1; open <= N; open++) {
        int start = open + 1;
        if (start == N + 1) start = 1;

        int sum = 0;
        int mult = 1;

        while (start != open) {
            // printf("mult: %d, R[start]: %d\n", mult, R[start]);
            sum += R[start] * mult;
            start++;
            mult++;
            if (start == N + 1) start = 1;
        }

        min_total = min(sum, min_total);
    }

    printf("%d\n", min_total);
}