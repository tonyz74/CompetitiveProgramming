#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    freopen("photo.in", "r", stdin);
    freopen("photo.out", "w", stdout);

    int N; cin >> N;

    vector<int> b(N);
    for (int i = 1; i <= N - 1; i++) {
        cin >> b[i];
    }

    for (int a1 = 1; a1 <= N; a1++) {
        vector<bool> seen(N + 1, false);
        seen[a1] = true;

        // construct the sequence that must follow
        vector<int> orig(N + 1, 0);
        orig[1] = a1;

        int curr_a = a1;
        for (int i = 1; i <= N - 1; i++) {
            int next_a = b[i] - curr_a;

            if (next_a <= 0 || next_a > N || seen[next_a]) {
                goto failure;
            }

            seen[next_a] = true;
            orig[i + 1] = next_a;
            curr_a = next_a;
        }

        for (int i = 1; i <= N; i++) {
            printf("%d", orig[i]);
            if (i != N) printf(" ");
        }
        printf("\n");

        failure: (void) 0;
    }
}