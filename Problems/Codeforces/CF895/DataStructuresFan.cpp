#include <iostream>
#include <vector>

using namespace std;

void solve(void) {
    int N;
    cin >> N;

    vector<int> A(N + 1, 0);

    for (int i = 1; i < N + 1; i++) {
        cin >> A[i];
    }

    string S;
    cin >> S;

    int Q;
    cin >> Q;

    vector<int> prefix_XOR(N + 1, 0);
    for (int i = 1; i < N + 1; i++) {
        prefix_XOR[i] = prefix_XOR[i - 1] ^ A[i];
    }

    int X0 = 0, X1 = 0;

    for (int i = 0; i < S.size(); i++) {
        int c = S[i];
        if (c == '0') {
            X0 ^= A[i + 1];
        } else {
            X1 ^= A[i + 1];
        }
    }

    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;

        // replace
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            int region_xor = prefix_XOR[r] ^ prefix_XOR[l-1];
            X0 ^= region_xor;
            X1 ^= region_xor;
        } else {
            int v;
            cin >> v;

            if (v == 0) printf("%d ", X0); else printf("%d ", X1);
        }
    }

    printf("\n");
}

int main(void) {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        solve();
    }
}