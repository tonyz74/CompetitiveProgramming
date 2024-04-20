#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

#define MAX_MEX (2 * (int) 1e5 + 10)

int main(void) {
    set<int> unused;

    int N, Q; cin >> N >> Q;
    vector<int> A(N);

    vector<int> freq(MAX_MEX + 1, 0);

    for (int i = 0; i < N; i++) {
        long long a; cin >> a;

        if (a <= N) freq[a]++;
        A[i] = a;
    }

    for (int i = 0; i <= MAX_MEX; i++) if (!freq[i]) unused.insert(i);

    while (Q--) {
        int i, x; cin >> i >> x;
        i--;

        if (x <= MAX_MEX) {
            if (freq[x] == 0) unused.erase(x);
            freq[x]++;
        }

        if (A[i] <= MAX_MEX) {
            if (freq[A[i]] == 1) {
                freq[A[i]] = 0;
                unused.insert(A[i]);
            } else {
                freq[A[i]] = max(freq[A[i]] - 1, 0);
            }
        }

        A[i] = x;

        printf("%d\n", *unused.begin());
    }
}