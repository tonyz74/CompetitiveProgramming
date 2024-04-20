#include <iostream>
#include <vector>
#include <string>

using namespace std;
using i64 = long long;

i64 pow2[64];
i64 N, L;
string S;

pair<i64, i64> get(i64 x) {
    i64 transform_L = L;
    while (transform_L < x) {
        transform_L *= 2;
    }

    i64 portion_idx = (transform_L / 2) - (transform_L - x);
    return make_pair(transform_L, portion_idx);
}

int main(void) {
    freopen("cowcode.in", "r", stdin);
    freopen("cowcode.out", "w", stdout);

    i64 p = 1;
    for (int i = 0; i <= 63; i++) {
        pow2[i] = p;
        p *= 2; 
    }

    cin >> S;
    cin >> N;
    // make it 1 indexed
    S = '.' + S;
    L = S.size() - 1;

    if (N <= L) {
        printf("%c\n", S[N]);
        return 0;
    }

    // 1 means the very front
    while (N > L) {
        pair<i64, i64> p = get(N);
        i64 seq_len = p.first;
        i64 off = p.second;

        // printf("iteration 1: %lld, %lld, N = %lld\n", seq_len, off, N);

        if (off == 1) {
            N = seq_len / 2;
        } else {
            N = off - 1;
        }
    }

    // printf("N was %lld\n", N);
    printf("%c\n", S[N]);
}